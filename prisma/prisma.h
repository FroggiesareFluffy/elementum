#ifndef PRISMA_PRISMA
#define PRISMA_PRISMA

#include "chroma/uniform"
#include <memory>

namespace prisma {

class Prisma {
 public:
  void LoadModel(const std::string& name, const Model& model);
  void Draw(const std::string& name, const shadow::Matrix& position,
	    const std::string& animation = "", int animation_step = 0);
  void SetView(const shadow::Matrix& view);
  void SetProjection(const shadow::Matrix& projection);
  void RenderScene();
 private:
  std::shared_ptr<chroma::Uniform> _viewmatrix_;
  std::shared_ptr<chroma::Uniform> _projectionmatrix_;
};
  
}  // namespace prisma

#endif
