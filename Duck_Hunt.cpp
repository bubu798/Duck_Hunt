# include "Duck_Hunt.h"


#include "core/engine.h"
#include "utils/gl_utils.h"

#include "lab_m1/lab3/transform2D.h" //you can find the original project here https://github.com/bubu798/EGC/tree/master/src 
					//you have the instructions in README.md
#include "lab_m1/lab3/object2D.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


    resolutionX = resolution.x; //limita din dreapta
    resolutionY = resolution.y; //limita de sus
    translateX = 0; //legea de miscare coord x
    translateY = 0; //legea de miscare coord y
    counter = 0;
    angularStep = 0;
    angularStep2 = 0;
    unghi = rand() % (25 - 75 + 1) + 25; //inclinarea initiala a ratei + directia de mers
    centruAripaX = 0;
    centruAripaY = 0;
    counter2 = 0;
    centruAripa2X = 0;
    centruAripa2Y = 0;
    scale = 8; //cu cat este scalata rata
    vitezaInitiala = 30;
    speedX = vitezaInitiala;
    speedY = vitezaInitiala;
    countEscape = 0;
    numarRate = 1;
    numarVieti = 3;
    numarGloante = 3;
    scor = 0;
    scorMax = 50;
    aMurit = false;
    aScapat = false;
    minusViata = true;
    GAMEOVER = false;

    {
        //aripa din stanga a unei rate
        vector<VertexFormat> verticesA1
        {
            VertexFormat(glm::vec3(0, 4, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesA1 =
        {
            0, 1, 2,
        };
        CreateMesh("aripa1", verticesA1, indicesA1);

        //aripa din dreapta a unei rate
        vector<VertexFormat> verticesA2
        {
            VertexFormat(glm::vec3(0, -4, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesA2 =
        {
            0, 1, 2,
        };
        CreateMesh("aripa2", verticesA2, indicesA2);

        //corpul unei rate
        vector<VertexFormat> verticesCorp
        {
            VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-5, 3, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-5, -3, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesCorp =
        {
            0, 1, 2,
        };
        CreateMesh("corp", verticesCorp, indicesCorp);

        //capul unei rate(cerc)
        vector <VertexFormat> verticesCap;
        int x = 0, y = 0, z = 0;
        float radius = 1.4;//raza cercului(lungimea unei laturi a unui triunghi)
        verticesCap.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.26, 0.45, 0.29), glm::vec3(0.2, 0.6, 0.8)));//varful tuturor triunghiurilor ce vor forma cercul
        for (int i = 0; i <= 30; i++) { //vom forma un cerc cu ajutorul a 30 de triunghiuri
            verticesCap.push_back(VertexFormat( glm::vec3(x + (radius * cos((float)i * 2 * M_PI / 30)), y + (radius * sin((float)i * 2 * M_PI / 30)), 0), glm::vec3(0.26, 0.45, 0.29), glm::vec3(0.2, 0.8, 0.6)));
        }
        vector<unsigned int> indicesCap;
        for (int i = 0; i <= 30; i++) {
            indicesCap.push_back(0);
            indicesCap.push_back(i + 1);
            indicesCap.push_back(i + 2);
        }
        CreateMesh("cap", verticesCap, indicesCap);

        //vietile
        vector <VertexFormat> verticesVieti;
        verticesVieti.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.6, 0.8)));//varful tuturor triunghiurilor ce vor forma cercul
        for (int i = 0; i <= 30; i++) { //vom forma un cerc cu ajutorul a 30 de triunghiuri
            verticesVieti.push_back(VertexFormat(glm::vec3(x + (radius * cos((float)i * 2 * M_PI / 30)), y + (radius * sin((float)i * 2 * M_PI / 30)), 0), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)));
        }
        vector<unsigned int> indicesVieti;
        for (int i = 0; i <= 30; i++) {
            indicesVieti.push_back(0);
            indicesVieti.push_back(i + 1);
            indicesVieti.push_back(i + 2);
        }
        CreateMesh("vieti", verticesVieti, indicesVieti);

        //ciocul unei rate
        vector<VertexFormat> verticesCioc
        {
            VertexFormat(glm::vec3(8, 0, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(5, 1, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(5, -1, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesCioc =
        {
            0, 1, 2,
        };
        CreateMesh("cioc", verticesCioc, indicesCioc);

        //iarba
        vector<VertexFormat> verticesIarba
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 8, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 8, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indicesIarba =
        {
            0, 1, 2,
            0, 2, 3,
        };
        CreateMesh("iarba", verticesIarba, indicesIarba);

        //scor
        vector<VertexFormat> verticesScor
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 8, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 8, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))
        };
        CreateMesh("scor", verticesScor, indicesIarba);

        //gloante
        vector<VertexFormat> verticesGloante
        {
            VertexFormat(glm::vec3(0, 4, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesGloante =
        {
            0, 1, 2,
        };
        CreateMesh("gloante", verticesGloante, indicesGloante);

        //scorMax
        vector<VertexFormat> verticesScorMax
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 8, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 8, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indicesScorMax =
        {
            0, 1, 2,
            0, 2, 3,
        };
        CreateMesh("scorMax", verticesScorMax, indicesScorMax);
    }
}

//functia care creaza obiectele
void Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // TODO(student): Create the VAO and bind it

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glEnableVertexAttribArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}



void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    //initializare matrici
    modelMatrix = glm::mat3(1);  //matricea ratei
    modelMatrixCap = glm::mat3(1);
    modelMatrixA1 = glm::mat3(1); //aripa stanga
    modelMatrixA2 = glm::mat3(1); //aripa dreapta
    modelMatrixIarba = glm::mat3(26); //iarba
    modelMatrixVieta1 = glm::mat3(15); //v1
    modelMatrixVieta1 *= transform2D::Translate(3, 45);
    modelMatrixVieta2 = glm::mat3(15); //v2
    modelMatrixVieta2 *= transform2D::Translate(7, 45);
    modelMatrixVieta3 = glm::mat3(15); //v3
    modelMatrixVieta3 *= transform2D::Translate(11, 45);
    modelMatrixScorMax = glm::mat3(1); //scorMax
    modelMatrixScorMax *= transform2D::Translate(resolutionX - 300, resolutionY - 100);
    modelMatrixScorMax *= transform2D::Scale(5, 5);
    modelMatrixScor = glm::mat3(1); //scor
    modelMatrixScor *= transform2D::Translate(resolutionX - 300, resolutionY - 100);
    modelMatrixScor *= transform2D::Scale((5 * float(scor)) / float(scorMax), 5);
    modelMatrixG1 = glm::mat3(7);
    modelMatrixG1 *= transform2D::Translate(6, 87);
    modelMatrixG2 = glm::mat3(7);
    modelMatrixG2 *= transform2D::Translate(15, 87);
    modelMatrixG3 = glm::mat3(7);
    modelMatrixG3 *= transform2D::Translate(24, 87);
    if (numarGloante < 3) {
        modelMatrixG3 *= transform2D::Translate(1000, 1000);
    }
    if (numarGloante < 2) {
        modelMatrixG2 *= transform2D::Translate(1000, 1000);
    }
    if (numarGloante < 1) {
        modelMatrixG1 *= transform2D::Translate(1000, 1000);
    }
    if (numarVieti < 3) {
        modelMatrixVieta3 *= transform2D::Translate(1000, 1000);
    }
    if (numarVieti < 2) {
        modelMatrixVieta2 *= transform2D::Translate(1000, 1000);
    }
    if (numarVieti < 1) {
        modelMatrixVieta1 *= transform2D::Translate(1000, 1000);
        GAMEOVER = true;
    }


    /*cout << "nr vieti " << numarVieti << endl;
    cout << "nr gloante " << numarGloante << endl;*/

    /*cout << speedX << " viteza" << endl;
    cout << countEscape << " merge secundele" << endl;*/

    //ciocniri rata
    if(translateX * scale > resolutionX - 15) {
        unghi = (180 - unghi);
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        //cout << "lovit dreapta" << endl;
    }
    if (translateX < 0) {
        unghi = (180 - unghi);
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        //cout << "lovit stanga " << endl;
    }
    if (translateY * scale > resolutionY) {
        unghi = -unghi;
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        //cout << "lovit sus" << endl;
    }
    if (translateY < 0) {
        if (!aMurit) {
            unghi = -unghi;
            modelMatrix *= transform2D::Rotate(RADIANS(unghi));
            //cout << "lovit jos" << endl;
        }
    }

    /*cout << "scapat " << aScapat << endl;
    cout << "murit " << aMurit << endl;*/

    //escape
    countEscape += deltaTimeSeconds;
    if ((countEscape >= 5 || numarGloante <= 0) && !aMurit) {
        speedX = 0;
        unghi = 90;
        aMurit = false;
        //aScapat = true;
        if (minusViata) {
            numarVieti--;
            minusViata = false;
        }
    }

    //respawn rata
    if (translateY * scale < -200 || translateY * scale > resolutionY + 200) {
        countEscape = 0;
        translateX = 0;
        translateY = 0;
        speedX = vitezaInitiala + numarRate / 5 * 20;
        speedY = vitezaInitiala + numarRate / 5 * 20;
        unghi = rand() % (25 - 75 + 1) + 25;
        /*cout << numarRate << " nrRate " << endl;
        cout << speedX << " speed " << endl;*/
        numarRate++;
        numarGloante = 3;
        aMurit = false;
        //aScapat = false;
        minusViata = true;
    }
 
    //miscarea ratei
    modelMatrix *= transform2D::Scale(scale, scale);
    translateX += speedX * deltaTimeSeconds * cos(RADIANS(unghi));
    translateY += speedY * deltaTimeSeconds * sin(RADIANS(unghi));
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(RADIANS(unghi));

    //pozitionare cap
    modelMatrixCap *= modelMatrix;
    modelMatrixCap *= transform2D::Translate(5, 0); 
    
    //miscare aripa stanga
    modelMatrixA1 *= modelMatrix;
    angularStep += deltaTimeSeconds * 10;
    counter += deltaTimeSeconds;
    if (counter >= 0.2) {
        angularStep = -angularStep;
        counter = 0.0;
        counter += deltaTimeSeconds;
    }
    centruAripaX = 0;
    centruAripaY = 4/3;
    centruAripaX += deltaTimeSeconds*5;
    centruAripaY += deltaTimeSeconds*5;
    modelMatrixA1 *= transform2D::Translate(centruAripaX, centruAripaY);
    modelMatrixA1 *= transform2D::Rotate(RADIANS(angularStep));
    modelMatrixA1 *= transform2D::Translate(-centruAripaX, -centruAripaY);

    //miscare aripa dreapta
    modelMatrixA2 *= modelMatrix;
    angularStep2 -= deltaTimeSeconds * 10;
    counter2 += deltaTimeSeconds;
    if (counter2 >= 0.2) {
        angularStep2 = -angularStep;
        counter2 = 0.0;
        counter2 += deltaTimeSeconds;
    }
    centruAripa2X = 0;
    centruAripa2Y = -4/3;
    centruAripa2X += deltaTimeSeconds * 5;
    centruAripa2Y += deltaTimeSeconds * 5;
    modelMatrixA2 *= transform2D::Translate(centruAripa2X, centruAripa2Y);
    modelMatrixA2 *= transform2D::Rotate(RADIANS(angularStep2));
    modelMatrixA2 *= transform2D::Translate(-centruAripa2X, -centruAripa2Y);

    //randare obiecte

    if (!GAMEOVER && scor != scorMax) {
        RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrixIarba);
        RenderMesh2D(meshes["aripa1"], shaders["VertexColor"], modelMatrixA1);
        RenderMesh2D(meshes["aripa2"], shaders["VertexColor"], modelMatrixA2);
        RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrixCap);
        RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["vieti"], shaders["VertexColor"], modelMatrixVieta1);
        RenderMesh2D(meshes["vieti"], shaders["VertexColor"], modelMatrixVieta2);
        RenderMesh2D(meshes["vieti"], shaders["VertexColor"], modelMatrixVieta3);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrixScor);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        RenderMesh2D(meshes["scorMax"], shaders["VertexColor"], modelMatrixScorMax);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        RenderMesh2D(meshes["gloante"], shaders["VertexColor"], modelMatrixG1);
        RenderMesh2D(meshes["gloante"], shaders["VertexColor"], modelMatrixG2);
        RenderMesh2D(meshes["gloante"], shaders["VertexColor"], modelMatrixG3);
    }
}


void Tema1::FrameEnd()
{

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        /*cout << "mouseX " << mouseX;
        cout << " mouseY " <<resolutionY - mouseY << endl;
        cout << " translateX " << scale * translateX;
        cout << " translateY " << scale * translateY << endl;*/
        if (mouseX<(translateX * scale + 50) && mouseX>(translateX * scale - 50) && (resolutionY - mouseY) < (translateY * scale + 50) && (resolutionY - mouseY) > (translateY * scale - 50)) {
                aMurit = true;
                //cout << "hit" << endl;
                unghi = -90;
                speedX = 0;
                scor++;
                numarGloante--;
                //cout << "scor " << scor << endl;
        }
        else {
            numarGloante--;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
