#include "skeleton.h"
#include "animation.h"

#include <spine/extension.h>

#include <x2d/graphics.h>
#include <x2d/graphics/batch.h>
#include <x2d/graphics/texture.h>

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

spSkeletonWrapper::spSkeletonWrapper(spSkeletonData *data, spAtlas *atlas) :
	m_data(data),
	m_atlas(atlas)
{
	m_worldVertices = MALLOC(float, SPINE_MESH_VERTEX_COUNT_MAX);
	m_self = spSkeleton_create(data);

	// Pre-load animation objects
	for(int i = 0; i < m_data->animationCount; i++) {
		spAnimation *anim = m_data->animations[i];
		m_animations[anim->name] = new spAnimationWrapper(m_self, anim);
	}
}

spSkeletonWrapper::~spSkeletonWrapper()
{
	for(int i = 0; i < m_data->animationCount; i++) {
		spAnimation *anim = m_data->animations[i];
		m_animations[anim->name]->release();
	}
	spAtlas_dispose(m_atlas);
	spSkeleton_dispose(m_self);
	spSkeletonData_dispose(m_data);
}

spAnimationWrapper *spSkeletonWrapper::findAnimation(const string &name)
{
	spAnimationWrapper *anim = m_animations.find(name) != m_animations.end() ? m_animations[name] : 0;
	if(anim) anim->addRef();
	return anim;
}

void spSkeletonWrapper::setPosition(const Vector2 &pos)
{
	m_self->x = pos.x;
	m_self->y = pos.y;
}

void spSkeletonWrapper::setFlipX(const bool flip)
{
	m_self->flipX = flip;
}

void spSkeletonWrapper::setFlipY(const bool flip)
{
	m_self->flipY = flip;
}

void spSkeletonWrapper::draw(Batch *batch)
{
	if(!batch)
		return;
	spSkeleton_updateWorldTransform(m_self);

	Vertex vertices[4];
	for(int i = 0; i < m_self->slotCount; i++)
	{
		spSlot *slot = m_self->drawOrder[i];
		spAttachment *attachment = slot->attachment;
		if(!attachment) continue;
		Texture *texture = 0;
		if(attachment->type == SP_ATTACHMENT_REGION)
		{
			spRegionAttachment* regionAttachment = SUB_CAST(spRegionAttachment, attachment);
			texture = (Texture*)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->skeleton->x, slot->skeleton->y, slot->bone, m_worldVertices);

			uchar r = uchar(m_self->r * slot->r * 255);
			uchar g = uchar(m_self->g * slot->g * 255);
			uchar b = uchar(m_self->b * slot->b * 255);
			uchar a = uchar(m_self->a * slot->a * 255);

			vertices[0].color.set(r, g, b, a);
			vertices[0].position.x = m_worldVertices[SP_VERTEX_X1];
			vertices[0].position.y = m_worldVertices[SP_VERTEX_Y1];
			vertices[0].texCoord.x = regionAttachment->uvs[SP_VERTEX_X1];
			vertices[0].texCoord.y = 1.0f - regionAttachment->uvs[SP_VERTEX_Y1];
				
			vertices[1].color.set(r, g, b, a);
			vertices[1].position.x = m_worldVertices[SP_VERTEX_X2];
			vertices[1].position.y = m_worldVertices[SP_VERTEX_Y2];
			vertices[1].texCoord.x = regionAttachment->uvs[SP_VERTEX_X2];
			vertices[1].texCoord.y = 1.0f - regionAttachment->uvs[SP_VERTEX_Y2];
				
			vertices[2].color.set(r, g, b, a);
			vertices[2].position.x = m_worldVertices[SP_VERTEX_X3];
			vertices[2].position.y = m_worldVertices[SP_VERTEX_Y3];
			vertices[2].texCoord.x = regionAttachment->uvs[SP_VERTEX_X3];
			vertices[2].texCoord.y = 1.0f - regionAttachment->uvs[SP_VERTEX_Y3];
				
			vertices[3].color.set(r, g, b, a);
			vertices[3].position.x = m_worldVertices[SP_VERTEX_X4];
			vertices[3].position.y = m_worldVertices[SP_VERTEX_Y4];
			vertices[3].texCoord.x = regionAttachment->uvs[SP_VERTEX_X4];
			vertices[3].texCoord.y = 1.0f - regionAttachment->uvs[SP_VERTEX_Y4];

			texture->addRef();
			batch->setTexture(texture);
			batch->addVertices(vertices, 4, QUAD_INDICES, 6);
			batch->setTexture(0);
		} /*else if (attachment->type == ATTACHMENT_MESH) {
			MeshAttachment* mesh = (MeshAttachment*)attachment;
			if (mesh->verticesCount > SPINE_MESH_VERTEX_COUNT_MAX) continue;
			texture = (Texture*)((AtlasRegion*)mesh->rendererObject)->page->rendererObject;
			MeshAttachment_computeWorldVertices(mesh, slot->skeleton->x, slot->skeleton->y, slot, worldVertices);

			Uint8 r = skeleton->r * slot->r * 255;
			Uint8 g = skeleton->g * slot->g * 255;
			Uint8 b = skeleton->b * slot->b * 255;
			Uint8 a = skeleton->a * slot->a * 255;
			vertex.color.r = r;
			vertex.color.g = g;
			vertex.color.b = b;
			vertex.color.a = a;

			Vector2u size = texture->getSize();
			for (int i = 0; i < mesh->trianglesCount; ++i) {
				int index = mesh->triangles[i] << 1;
				vertex.position.x = worldVertices[index];
				vertex.position.y = worldVertices[index + 1];
				vertex.texCoords.x = mesh->uvs[index] * size.x;
				vertex.texCoords.y = mesh->uvs[index + 1] * size.y;
				vertexArray->append(vertex);
			}

		} else if (attachment->type == ATTACHMENT_SKINNED_MESH) {
			SkinnedMeshAttachment* mesh = (SkinnedMeshAttachment*)attachment;
			if (mesh->uvsCount > SPINE_MESH_VERTEX_COUNT_MAX) continue;
			texture = (Texture*)((AtlasRegion*)mesh->rendererObject)->page->rendererObject;
			SkinnedMeshAttachment_computeWorldVertices(mesh, slot->skeleton->x, slot->skeleton->y, slot, worldVertices);

			Uint8 r = skeleton->r * slot->r * 255;
			Uint8 g = skeleton->g * slot->g * 255;
			Uint8 b = skeleton->b * slot->b * 255;
			Uint8 a = skeleton->a * slot->a * 255;
			vertex.color.r = r;
			vertex.color.g = g;
			vertex.color.b = b;
			vertex.color.a = a;

			Vector2u size = texture->getSize();
			for (int i = 0; i < mesh->trianglesCount; ++i) {
				int index = mesh->triangles[i] << 1;
				vertex.position.x = worldVertices[index];
				vertex.position.y = worldVertices[index + 1];
				vertex.texCoords.x = mesh->uvs[index] * size.x;
				vertex.texCoords.y = mesh->uvs[index + 1] * size.y;
				vertexArray->append(vertex);
			}
		}*/
	}
}

spSkeletonData *spSkeletonWrapper::data() const
{
	return m_data;
}

spSkeleton *spSkeletonWrapper::get() const
{
	return m_self;
}

spSkeletonWrapper *spSkeletonWrapper::Factory(const string &jsonFile, const string &atlasFile, const float scale)
{
	spAtlas *atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
	spSkeletonJson* json = spSkeletonJson_create(atlas);
	json->scale = scale;
	spSkeletonData *data = spSkeletonJson_readSkeletonDataFile(json, jsonFile.c_str());
	if(!data) {
		LOG("spSkeleton.Factory: %s", json->error);
		return 0;
	}
	LOG("spSkeleton.Constructor: Default skin name '%s'", data->defaultSkin->name);
	spSkeletonJson_dispose(json);
	return new spSkeletonWrapper(data, atlas);
}