#pragma once
#include "vertex_output.h"
#include "frame_buffer.h"
#include "model.h"
#include "material.h"
using namespace std;

namespace SoftRender {
    class RenderSystem {
    public:
        void initialize(window_info info);
        void pipeLine();
        void tick(float time);

        void addModel(Model _model);
        Model* getOneModel(int index = 0);

        Material* getCurMatrial() { return m_tempMtl; }
        mat4 getCurModelMat() { return m_tempModelMat; }

    private:
        //视口变换
        mat4 getViewPortMatrix(int x, int y, int width, int height);

        void PerspectiveDivision(VertexOutput& v);

        //光栅化
        void rasterize(VertexOutput v1, VertexOutput v2, VertexOutput v3);
        void scanTriangle(VertexOutput v1, VertexOutput v2, VertexOutput v3);
        void scanLine(VertexOutput v1, VertexOutput v2);
        void drawMesh(Mesh tempMesh, Object tempObject);

        //各类形状
        void drawModel();
    private:
        vector<Model> m_model;
        FrameBuffer m_buffer;
        Material* m_tempMtl;
        mat4 m_tempModelMat;
    };
}