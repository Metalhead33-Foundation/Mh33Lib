#ifndef MHPIPELINE_HPP
#define MHPIPELINE_HPP
#include <MhLib/Media/GFX/MhGFXHandle.hpp>
#include <MhLib/Media/GFX/MhVertexSignature.hpp>
#include <MhLib/Media/GFX/MhShaderModule.hpp>
#include <MhLib/Media/GFX/MhIndexedMesh.hpp>
#include <MhLib/Media/GFX/MhUnindexedMesh.hpp>

namespace MH33 {
namespace GFX {

class Pipeline {
public:
	virtual Handle getNativeHandle() const = 0;
	virtual const VertexAttributeList* getVertexSignature() const = 0;
	virtual bool attachShaderModule(ShaderModule& module) = 0;
	virtual void assemble() = 0;
	virtual void draw(const UnindexedMesh& mesh) const = 0;
	virtual void draw(const IndexedMesh& mesh) const = 0;
	// Okay, now let's add stuff!
};

}
}
#endif // MHPIPELINE_HPP
