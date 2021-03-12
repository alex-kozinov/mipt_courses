// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

const int N = 20;
const int TOTAL_COORDS = 72 * N * N;
GLfloat g_vertex_buffer_data[TOTAL_COORDS];
GLfloat g_color_buffer_data[TOTAL_COORDS];

float NormDistance(vec3 vec) {
    return sqrt(vec.x *  vec.x + vec.y * vec.y + vec.z * vec.z);
}

vec3 GetPointColor(vec3 point) {
    vec3 whitePoint(2, 0, 0);
    vec3 bluePoint(0, 3, 0);
    
    float whiteCoef = float(1) / (float(1) + NormDistance(point - whitePoint) / 3);
    float blueCoef = abs(point.z) / 3;
    return float(0.5) * (whiteCoef * vec3(1, 1, 1) + (float(1) - whiteCoef) * vec3(1, 0, 0) + blueCoef * vec3(0, 0, 1) + (float(1) - blueCoef) * vec3(1, 0, 0));
}

int AppendPointSphereProjection(GLfloat *vertices, GLfloat *colors, vec3 point, float r) {
    float norm = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
    point = point / norm * r;
    vertices[0] = point.x;
    vertices[1] = point.y;
    vertices[2] = point.z;
    
    vec3 color = GetPointColor(point);
    colors[0] = color.x;
    colors[1] = color.y;
    colors[2] = color.z;
    
    return 3;
}

int AppendTriangulatedTriangleSphereProjection(GLfloat *vertices, GLfloat *colors, vec3 a, vec3 b, vec3 c, float r) {
    vec3 ac = c - a;
    vec3 ab = b - a;
    int totalSteps = 0;
    for (int i = 0; i < N; ++i) {
        for(int j = 0; j < 2 * (N - i) - 1; ++j) {
            for(int k = 0; k < 3; ++k) {
                float acStep = 0;
                float abStep = 0;
                if(j  % 2 == 0) {
                    acStep = float(i + (k == 2)) / float(N);
                    abStep = float(j / 2 + (k == 1)) / float(N);
                } else {
                    acStep = float(i + (k != 0)) / float(N);
                    abStep = float((j - 1) / 2 + (k != 1)) / float(N);
                }
                
                vec3 point = a + ab * abStep + ac * acStep;
                int step = AppendPointSphereProjection(vertices + totalSteps, colors + totalSteps, point, r);
                totalSteps += step;
            }
        }
    }
    return totalSteps;
}


void AppendSphere(GLfloat *vertices, GLfloat *colors, double r) {
    
    float xCoords[4] = {r, 0, -r, 0};
    float zCoords[4] = {0, -r, 0, r};
    
    int totalSteps = 0;
    for (int i = 0; i < 4; ++i) {
        for (int k = -1; k < 2; k += 2) {
            int j = (i + 1) % 4;
            vec3 a = vec3(xCoords[i], 0, zCoords[i]);
            vec3 b = vec3(xCoords[j], 0, zCoords[j]);
            vec3 c = vec3(0, float(k) * r, 0);
            
            int step = AppendTriangulatedTriangleSphereProjection(
                                                       vertices + totalSteps,
                                                       colors + totalSteps,
                                                       a, b, c,
                                                       r);
            totalSteps += step;
        }
    }
}

glm::vec3 GetCameraPositionByCircleTrajectory(double t, double r) {
//    return glm::vec3(cos(2*M_PI*t), sin(2*M_PI*t), 3);
    return glm::vec3(r * cos(2*M_PI*t), 0, r * sin(2*M_PI*t));
}

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Sphere", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    AppendSphere(g_vertex_buffer_data, g_color_buffer_data, 2);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    double startTime = glfwGetTime();
    const float fullRotateSeconds = 5;
    do{
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - startTime;
        double rotateNumber = deltaTime / fullRotateSeconds;
        double t = rotateNumber - double(int(rotateNumber));
        //first of all, lets change MVP
        glm::mat4 View = glm::lookAt(
            GetCameraPositionByCircleTrajectory(t, 8),
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, TOTAL_COORDS); // 12*3 indices starting at 0 -> 12 triangles

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

