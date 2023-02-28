#pragma once

#include <vector>
#include "components/simple_scene.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);


        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix;
        glm::mat3 modelMatrixCap;
        glm::mat3 modelMatrixA1;
        glm::mat3 modelMatrixA2;
        glm::mat3 modelMatrixIarba;
        glm::mat3 modelMatrixVieta1;
        glm::mat3 modelMatrixVieta2;
        glm::mat3 modelMatrixVieta3;
        glm::mat3 modelMatrixScorMax;
        glm::mat3 modelMatrixScor;
        glm::mat3 modelMatrixG1;
        glm::mat3 modelMatrixG2;
        glm::mat3 modelMatrixG3;
        float refX, refY;
        float resolutionX, resolutionY;
        float translateX, translateY;
        float centruAripaX, centruAripaY;
        float centruAripa2X, centruAripa2Y;
        float counter;
        float counter2;
        float angularStep;
        float angularStep2;
        float unghi;
        float scale;
        float speedX, speedY;
        float scaleX, scaleY;
        float countEscape;
        float countEscape2;
        int numarRate;
        int numarVieti;
        int numarGloante;
        int scor;
        int scorMax;
        float vitezaInitiala;
        bool aMurit;
        bool aScapat;
        bool minusViata;
        bool GAMEOVER;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1