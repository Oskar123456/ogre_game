// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Ogre.h"
#include "OgreApplicationContext.h"

Ogre::Root* root;
Ogre::SceneManager* scnMgr;

//! [key_handler]
class KeyHandler : public OgreBites::InputListener
{
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        if (evt.keysym.sym == OgreBites::SDLK_PAGEUP) {
            Ogre::Camera* cam = scnMgr->getCamera("MainCamera");
            Ogre::SceneNode* cam_ns = cam->getParentSceneNode();
            cam_ns->translate(Ogre::Vector3(0, 0.3f, 0));
        }
        if (evt.keysym.sym == OgreBites::SDLK_PAGEDOWN) {
            Ogre::Camera* cam = scnMgr->getCamera("MainCamera");
            Ogre::SceneNode* cam_ns = cam->getParentSceneNode();
            cam_ns->translate(Ogre::Vector3(0, -0.3f, 0));
        }
        if (evt.keysym.sym == OgreBites::SDLK_UP) {
            Ogre::Camera* cam = scnMgr->getCamera("MainCamera");
            Ogre::SceneNode* cam_ns = cam->getParentSceneNode();
            cam_ns->translate(Ogre::Vector3(0, 0, -0.3f));
        }
        if (evt.keysym.sym == OgreBites::SDLK_DOWN) {
            Ogre::Camera* cam = scnMgr->getCamera("MainCamera");
            Ogre::SceneNode* cam_ns = cam->getParentSceneNode();
            cam_ns->translate(Ogre::Vector3(0, 0, 0.3f));
        }
        return true;
    }
};
//! [key_handler]

int main(int argc, char *argv[])
{
//! [constructor]
    OgreBites::ApplicationContext ctx("OgreTutorialApp");
    ctx.initApp();
//! [constructor]

//! [setup]
    // get a pointer to the already created root
    root = ctx.getRoot();
    scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(6, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("MainCamera");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    ctx.getRenderWindow()->addViewport(cam);

    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

    Ogre::Entity* ninjaEntity = scnMgr->createEntity("ninja.mesh");
    ninjaEntity->setCastShadows(true);
    Ogre::SceneNode* ninja_node = scnMgr->getRootSceneNode()->createChildSceneNode();
    ninja_node->translate(Ogre::Vector3(2, 0, 2));

    ninja_node->attachObject(ninjaEntity);
//! [setup]

//! [main]
    // register for input events
    KeyHandler keyHandler;
    ctx.addInputListener(&keyHandler);

    ctx.getRoot()->startRendering();
    ctx.closeApp();
//! [main]
    return 0;
}
