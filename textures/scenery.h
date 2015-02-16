/* scenery.h */

#ifndef _SCENERY_H_
#define _SCENERY_H_


class Scene{
public:
    enum SceneType{DEFAULT, DESERT, GRASS};

    Scene();

    void change(SceneType new_scene);
    void draw();

private:
    SceneType current_scene;
};


/*
    The default constructor initializes the scene type to the default.
*/
inline Scene::Scene(){
    current_scene = DEFAULT;
}


/*
    This method changes the current scene.
    args: SceneType scene - the type of the new scene.
*/
inline void Scene::change(SceneType scene){
    current_scene = scene;
}



#endif
