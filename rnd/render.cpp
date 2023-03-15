/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 15.03.2023
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"


void RenderInit(GLFWwindow* window) {
    vector<vertex> v;
    vector<uint> i;
    topo::grid<vertex>(v, i, 10, 10, 4, 4);
    prim* smth = new prim(v, i);
    
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(45.0f * 0), vec3(1, 0, 0));
    
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, -0.5f, -2.0f));
    
    mat4 projection = mat4(1.0f);
    projection = perspective(radians(90.0f), (float)ani.w / (float)ani.h, 0.01f, 1000.0f);
    
    smth->projection = projection;
    smth->view = view;
    smth->model = model;
    
    ani.SetTexture(smth, "src/brick-wall/diff.tga");
    ani.SetTexture(smth, "src/brick-wall/nor.tga");

    // ani.AddPrim(smth);

    topo::sphere<vertex>(v, i, 2, 30, 30);
    prim* sph = new prim(v, i);
    sph->projection = projection;
    sph->view = view;
    sph->model = translate(mat4(1.0f), vec3(0, 4, 0)) * rotate(model, radians(-90.f), vec3(1, 0, 0));
    ani.SetTexture(sph, "src/earth.jpg");

    mtl* src = new mtl(vec3(0), vec3(0.5, 0, 0), vec3(0.7, 0.6, 0.6), 0.25);
    src->name = "red-plastic";
    ani.SetMaterial(sph, src);
    ani.AddPrim(sph);

    ani.SetMaterial(smth, "red-plastic");
    ani.AddPrim(smth);

    prim* light = new prim(v, i);
    light->projection = projection;
    light->view = view;
    light->model = translate(mat4(1.0f), vec3(1)) * scale(mat4(1.0f), vec3(0.1));
    ani.SetShader(light, "rnd/shd/LIGHT/");
    ani.AddPrim(light);
}


void Render(GLFWwindow* window) {
    // glClearColor(0.17, 0.1603, 0.209, 1);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (ani.is_wire_frame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    vector<prim*> prs;
    ani.GetPrims(&prs);
    vec3 pos = ani.cam.GetPos();
    for (auto pr : prs) {
        pr->view = ani.cam.GetView();
        pr->Draw();
        pr->shd->SetUniform("cam_pos", shader::uniform_types::VEC3, &pos);
    }

    ani.UpdateTimer(ani.is_pause);
    FlyingWASD();
    ani.dx = ani.dy = 0;
}

/* END OF 'render.cpp' FILE */
