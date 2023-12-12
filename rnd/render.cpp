/* Property of Cherepkov Petr
 * FILE: 'render.cpp'
 * LAST UPDATE: 26.03.2023
 */

/* rendering functions */

#include "render.h"
#include "../utils/utils.h"
#include "./lighting/lighting.h"


void RenderInit(GLFWwindow* window) {
    vector<vertex> v;
    vector<uint> i;
    topo::grid<vertex>(v, i, 10, 10, 1, 1);
    prim* smth = new prim(v, i);
    
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(45.0f * 0), vec3(1, 0, 0));
    
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, -0.5f, -2.0f));
    
    mat4 projection = mat4(1.0f);
    projection = perspective(radians(90.0f), (float)ani.w / (float)ani.h, 0.01f, 1000.0f);

    object* obj = new object();
    obj->projection = projection;
    ani.AddObj(obj);
    
    smth->model = model;
    
    ani.SetTexture(smth, "src/brick-wall/diff.tga");
    ani.SetTexture(smth, "src/brick-wall/nor.tga");

    topo::sphere<vertex>(v, i, 2, 30, 30);
    prim* sph = new prim(v, i);
    sph->model = translate(mat4(1.0f), vec3(0, 4, 0)) * rotate(model, radians(-90.f), vec3(1, 0, 0));
    ani.SetTexture(sph, "src/earth.jpg");

    mtl* src = new mtl(vec3(0), vec3(0.5, 0, 0), vec3(0.7, 0.6, 0.6), 0.25);
    src->name = "red-plastic";
    ani.SetMaterial(sph, src);
    ani.AddPrim(obj, sph);

    ani.SetMaterial(smth, "default");
    ani.AddPrim(obj, smth);

    lights::point* P = new lights::point();
    P->pos = vec3(1);
    P->ka = vec3(1, 0.5, 0.5);
    P->kd = vec3(1, 0.5, 0.5);
    P->ks = vec3(1, 0.5, 0.5);
    P->shds.push_back(ani.GetShd("rnd/prim/shd/DEFAULT/"));
    ani.AddLight(P);
    P->Apply();

    lights::point* P2 = new lights::point();
    P2->pos = vec3(-2, 2, -2);
    P2->shds.push_back(ani.GetShd("rnd/prim/shd/DEFAULT/"));
    ani.AddLight(P2);
    P2->Apply();

    lights::direct* D = new lights::direct();
    D->dir = normalize(-vec3(6, 2, -1));
    D->ka = vec3(0.12, 0.12, 0.3);
    D->kd = vec3(0);
    D->ks = vec3(0);
    D->shds.push_back(ani.GetShd("rnd/prim/shd/DEFAULT/"));
    ani.AddLight(D);
    D->Apply();

    lights::spot* S = new lights::spot();
    S->pos = vec3(0, 12, 0);
    S->dir = vec3(0, -1, 0);
    S->ka = vec3(0.3, 0.3, 1);
    S->kd = vec3(0.3, 0.3, 1);
    S->ks = vec3(0.3, 0.3, 1);
    S->shds.push_back(ani.GetShd("rnd/prim/shd/DEFAULT/"));
    ani.AddLight(S);
    S->Apply();
}


void Render(GLFWwindow* window) {
    // glClearColor(0.17, 0.1603, 0.209, 1);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (ani.is_wire_frame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    vector<object*> objs;
    ani.GetObjs(&objs);
    vec3 pos = ani.cam.GetPos();
    for (auto obj : objs) {
        obj->view = ani.cam.GetView();
        obj->Draw();
        obj->shd->SetUniform("cam_pos", shader::VEC3, &pos);
    }

    ani.UpdateTimer(ani.is_pause);
    FlyingWASD();
    ani.dx = ani.dy = 0;
}

/* END OF 'render.cpp' FILE */
