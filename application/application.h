#pragma once

#include <tov/core.h>

#include <tov/math/radian.h>
#include <tov/math/quaternion.h>
#include <tov/math/radian.h>
#include <tov/math/vector.h>

#include <tov/rendering/backend.h>

#include <tov/rendering/colour.h>
#include <tov/rendering/camera.h>
#include <tov/rendering/image.h>
#include <tov/rendering/material.h>
#include <tov/rendering/pixel_format.h>

#include <tov/rendering/geometry/cube.h>
#include <tov/rendering/geometry/sphere.h>

#include <tov/rendering/entity.h>
#include <tov/rendering/mesh_component.h>
#include <tov/rendering/mesh/mesh.h>
#include <tov/rendering/mesh/mesh_manager.h>
#include <tov/rendering/mesh/submesh.h>

#include <tov/rendering/buffers/vertex_buffer_format.h>
#include <tov/rendering/buffers/vertex_format.h>
#include <tov/rendering/mesh/vertex_data_format.h>

#include <tov/rendering/texture/texture.h>

#include <tov/rendering/buffers/pixel_buffer_object.h>

#include <tov/rendering/render_system.h>
#include <tov/rendering/render_window.h>
#include <tov/rendering/scene_node.h>
#include <tov/rendering/viewport.h>
#include <tov/rendering/scene/scene.h>
#include <tov/rendering/scene/skybox.h>

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
using Clock = std::chrono::high_resolution_clock;


class Application
{
public:
    Application(
        const char* windowName,
        tov::rendering::WindowPlatformSupport* platformSupport,
        tov::rendering::WindowRendererSupport* rendererSupport
    )
        : mPlatformSupport(platformSupport)
        , mRendererSupport(rendererSupport)
        , mAccumulator(0ns)
    {
        mRenderSystem = tov::rendering::backend::createRenderSystem(*platformSupport, *rendererSupport);

        mScene = new tov::rendering::scene::Scene(*mRenderSystem);
        mCamera = &mScene->createCamera();

        auto& window = mRenderSystem->createRenderWindow(windowName, 800, 600, false);
        auto colour = tov::rendering::Colour::Blue;
        std::cout << "color dfadfad: " << tov::rendering::Colour::Blue.r << "\n";
        std::cout << "color dfadfad: " << tov::rendering::Colour::Blue.b << "\n";
        std::cout << "color dfadfad: " << tov::rendering::Colour::Blue.g << "\n";

        auto& vp = window.createViewport(2, 0.0f, 0.0f, 1.0f, 1.0f, colour);
        std::cout << "addr of vp : " << &vp << "\n";
        std::cout << "color of vp: " << vp.getBackgroundColour() << "\n";
        mCamera->attachViewport(vp);
        mRenderSystem->initialize();

        auto& root = mScene->getRootNode();
        mCameraNode = &root.createChild();
        mCameraNode->attachSceneObject(mCamera);

        //createSkybox();
        createMaterials();
        createNodes();
    }

    void start()
    {
        while (1)
        {
            iterate();
        }
    }

    void call()
    {
        iterate();
    }

private:
    void createSkybox()
    {
        auto& bufferManager = *mRenderSystem->getBufferManager();

        auto texture = (tov::rendering::texture::Texture*)nullptr;
        {
            auto image = tov::rendering::Image("./assets/church.jpg");
            auto pixelFormat = image.getPixelFormat();
            texture = &mRenderSystem->createTexture2D(image.getWidth(), image.getHeight(), pixelFormat);

            auto size = image.getSize();
            auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
            auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

            auto data = image.data();
            pbo.updatePixelData(data, size);
            texture->unpackPixelData(pbo);
        }

        mSkybox = new tov::rendering::scene::Skybox(*mRenderSystem, texture);
        mScene->setSkybox(mSkybox);
    }

    void createMaterials()
    {
        auto& bufferManager = *mRenderSystem->getBufferManager();

        {
            auto pixelFormat = tov::rendering::PixelFormat(8, 8, 8, 8, 0, 0);
            auto& texture = mRenderSystem->createTexture2D(16, 16, pixelFormat);

            auto size = 16u * 16u * pixelFormat.getSize();
            auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
            auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

            auto buffer = new unsigned char[size];
            for (auto i = 0u; i < size; i += 4)
            {
                buffer[i + 0] = 122;
                buffer[i + 1] = 0;
                buffer[i + 2] = 255;
                buffer[i + 3] = 255;
            }
            pbo.updatePixelData(buffer, size);
            delete[] buffer;

            texture.unpackPixelData(pbo);

            mColourMaterial = new tov::rendering::Material();
            mColourMaterial->setAlbedoMap(&texture);
        }

        {
            auto image = tov::rendering::Image("./assets/skybox.png");
            auto pixelFormat = image.getPixelFormat();
            auto& texture = mRenderSystem->createTexture2D(image.getWidth(), image.getHeight(), pixelFormat);

            auto size = image.getSize();
            auto& pixelBuffer = *bufferManager.createPixelUnpackBuffer(pixelFormat, size);
            auto pbo = tov::rendering::buffers::PixelBufferObject(pixelBuffer, pixelFormat);

            auto data = image.data();
            pbo.updatePixelData(data, size);
            texture.unpackPixelData(pbo);

            mTextureMaterial = new tov::rendering::Material();
            mTextureMaterial->setAlbedoMap(&texture);
        }
    }

    void createNodes()
    {
        auto& meshManager = *mRenderSystem->getMeshManager();

        auto vertexDataFormat = tov::rendering::mesh::VertexDataFormat();
        {
            tov::rendering::buffers::VertexFormat vf;
            vf.addAttribute(tov::rendering::buffers::VertexAttribute::POSITION, 0);
            vf.addAttribute(tov::rendering::buffers::VertexAttribute::NORMAL, 1);
            vf.addAttribute(tov::rendering::buffers::VertexAttribute::TEXTURE_COORDINATE, 2);
            tov::rendering::buffers::VertexBufferFormat vbf(
                tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED,
                vf
            );
            vertexDataFormat.mapHandleToFormat(0, vbf);
        }

        auto sphereMesh = meshManager.create();
        {
            auto sphere = tov::rendering::geometry::Sphere(5.0f);
            auto& submesh = sphereMesh->createSubmesh(sphere, vertexDataFormat);
            submesh.setMaterial(*mColourMaterial);
        }

        auto cuboidMesh = meshManager.create();
        {
            auto cuboid = tov::rendering::geometry::Cube(5.0f);
            auto& submesh = cuboidMesh->createSubmesh(cuboid, vertexDataFormat);
            submesh.setMaterial(*mTextureMaterial);
        }

        {
            auto& entityNode = mScene->getRootNode().createChild();
            auto& entity = mScene->createEntity();
            entity.createMeshComponent(*sphereMesh);
            entityNode.attachSceneObject(&entity);
            tov::math::Vector3 translation(0, 0, -40);
            entityNode.getTransform().setTranslation(translation);
        }

        {
            auto& entityNode = mScene->getRootNode().createChild();
            auto& entity = mScene->createEntity();
            entity.createMeshComponent(*sphereMesh);
            entityNode.attachSceneObject(&entity);
            tov::math::Vector3 translation(5, 5, -30);
            entityNode.getTransform().setTranslation(translation);
        }

        {
            auto& entityNode = mScene->getRootNode().createChild();
            auto& entity = mScene->createEntity();
            entity.createMeshComponent(*cuboidMesh);
            entityNode.attachSceneObject(&entity);
            tov::math::Vector3 translation(-2, 0, -15);
            entityNode.getTransform().setTranslation(translation);

            //mNode = &entityNode;
        }
    }

    void iterate()
    {
        //const std::chrono::milliseconds timestep(16ms);

        //auto now = Clock::now();
        //auto deltaTime = now - mCurrentTime;
        //mCurrentTime = now;

        //mAccumulator += deltaTime;

        //while (mAccumulator >= timestep)
        //{
        //    mAccumulator -= timestep;
        //}

        //auto alpha = (float)mAccumulator.count() / std::chrono::duration_cast<std::chrono::nanoseconds>(timestep).count();

        //{
        //    auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
        //    auto angle = tov::math::Radian(0.01f) * alpha;
        //    auto rotation = tov::math::Quaternion(angle, axis);
        //    //mNode->getTransform().rotate(rotation);
        //}

        //{
        //    auto axis = tov::math::Vector3(0.0f, 1.0f, 0.0f);
        //    auto angle = tov::math::Radian(0.001f) * alpha;
        //    auto rotation = tov::math::Quaternion(angle, axis);
        //    //mCameraNode->getTransform().rotate(rotation);
        //}

        mRenderSystem->renderFrame(*mScene);
        mRenderSystem->swapBuffers();
    }

private:
    tov::rendering::WindowPlatformSupport* mPlatformSupport;
    tov::rendering::WindowRendererSupport* mRendererSupport;

    tov::rendering::RenderSystem* mRenderSystem;

    tov::rendering::scene::Skybox* mSkybox;

    tov::rendering::scene::Scene* mScene;
    tov::rendering::SceneNode* mNode;

    tov::rendering::Camera* mCamera;
    tov::rendering::SceneNode* mCameraNode;

    tov::rendering::Material* mColourMaterial;
    tov::rendering::Material* mTextureMaterial;

    std::chrono::nanoseconds mAccumulator;
    std::chrono::time_point<Clock> mCurrentTime = Clock::now();
};
