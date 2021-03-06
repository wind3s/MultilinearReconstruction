#ifndef FACESHAPEFROMSHADING_OFFSCREENMESHVISUALIZER_H
#define FACESHAPEFROMSHADING_OFFSCREENMESHVISUALIZER_H

//#include "Geometry/geometryutils.hpp"
//#include "Utils/utility.hpp"

#include "basicmesh.h"
#include "parameters.h"

#include <QImage>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOffscreenSurface>

#include <boost/timer/timer.hpp>

class OffscreenMeshVisualizer {
public:
  enum MVPMode {
    OrthoNormal,
    CamPerspective,
    BackgroundImage
  };
  enum RenderMode {
    Texture,
    Normal,
    Mesh,
    MeshAndImage,
    TexturedMesh
  };
  OffscreenMeshVisualizer(int width, int height)
   : width(width), height(height), index_encoded(true), lighting_enabled(false) {}

  void BindMesh(const BasicMesh& in_mesh) {
    mesh = in_mesh;
  }
  void BindTexture(const QImage& in_texture) {
    texture = in_texture;
  }
  void BindImage(const QImage& img) {
    image = img;
  }
  void SetMeshRotationTranslation(const Vector3d& R, const Vector3d& T) {
    mesh_rotation = R;
    mesh_translation = T;
  }
  void SetCameraParameters(const CameraParameters& cam_params) {
    camera_params = cam_params;
  }
  void SetFacesToRender(const vector<int>& indices) {
    faces_to_render = indices;
  }

  void SetRenderMode(RenderMode mode_in) {
    render_mode = mode_in;
  }
  void SetMVPMode(MVPMode mode_in) {
    mode = mode_in;
  }
  void SetIndexEncoded(bool val) {
    index_encoded = val;
  }
  void SetEnableLighting(bool val) {
    lighting_enabled = val;
  }

  QImage Render(bool multi_sampled=false) const;
  pair<QImage, vector<float>> RenderWithDepth(bool multi_sampled=false) const;

protected:
  void SetupViewing(const MVPMode&) const;
  void CreateTexture() const;
  void EnableLighting() const;
  void DisableLighting() const;

private:
  int width, height;
  MVPMode mode;
  RenderMode render_mode;

  Vector3d mesh_rotation, mesh_translation;
  CameraParameters camera_params;

  mutable vector<int> faces_to_render;

  bool index_encoded;
  bool lighting_enabled;
  BasicMesh mesh;
  QImage image;
  mutable GLuint image_tex;
  QImage texture;
  mutable glm::dmat4 Mview;
};


#endif //FACESHAPEFROMSHADING_OFFSCREENMESHVISUALIZER_H
