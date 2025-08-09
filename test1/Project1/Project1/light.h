#pragma once
#include "global_context.h"
namespace SoftRender
{
	class Light {
	public:
		glm::vec3 m_postion;
		//Color 漫反射颜色程度（0 - 1之间 1: 为原色，0全黑）
		glm::vec3 m_color;
		//Specular 镜面光程度 同漫反射颜色
		glm::vec3 m_specular;
		glm::vec3 m_direction;
		//强度i
		float m_intensity;

		virtual ~Light() {
		}
		Light(
			const glm::vec3& pos = glm::vec3(0, 0, 0),
			const glm::vec3& color = glm::vec3(0, 0, 0),
			const glm::vec3& specular = glm::vec3(0, 0, 0),
			const glm::vec3& dir = glm::vec3(0, -1, 0),
			const float& i = 1.0f) :
			m_postion(pos),
			m_color(color),
			m_specular(specular),
			m_direction(dir),
			m_intensity(i)
		{}

		virtual vec3 computeLight() {
			return vec3();
		}

		//反射的计算 2n * cos(n,l) - l = r
		//lightDir是光指向片段的方向
		vec3 reflectDir(const glm::vec3& lightDir, const glm::vec3& normal) {

			return lightDir - 2 * glm::dot(normal, lightDir) * normal;
		}
	};

	class DirectionLight : public Light {
		DirectionLight(vec3 dir = normalize(vec3(0, -1, 1)),
			vec3 color = normalize(vec3(0, 0, 0)),
			vec3 specular = normalize(vec3(0, 0, 0)),
			float intensity = 0.5) : Light(vec3(), dir, color, specular) 
		{
		}


		vec3 computeLight(vec3 worldPos, vec3 worldNormal, vec3 worldViewDir, vec3 albedo)
		{
			auto albedoDiff = std::max(dot(worldNormal, -m_direction), 0.f);
			auto reflectDir = this->reflectDir(m_direction, worldNormal);
			auto specularDiff = std::max(dot(worldNormal, -reflectDir), 0.f);

			auto albedoAns = m_color * albedoDiff * albedo;
			auto specularAns = m_specular * specularDiff;

			return (albedoAns + specularAns) * m_intensity;
		}
	};

	class PointLight : public Light {
	public:
		float m_k0;
		float m_k1;
		float m_k2;

		PointLight(vec3 pos = vec3(0, 0, 0),
			vec3 color = normalize(vec3(0, 0, 0)),
			vec3 specular = normalize(vec3(0, 0, 0)),
			float intensity = 0.5, float k0 = 1.0, float k1 = 0.09, float k2 = 0.032) : Light(pos, vec3(), color, specular)
		{
			m_k0 = k0;
			m_k1 = k1;
			m_k2 = k2;
		}

		vec3 computeLight(vec3 worldPos, vec3 worldNormal, vec3 worldViewDir, vec3 albedo)
		{
			float disOffset = distance(worldPos, m_postion);
			float insOffset = 1.0 / (m_k0 + m_k1 * disOffset + m_k2 * (disOffset * disOffset));
			
			auto lightDir = normalize(worldPos - m_postion);
			auto albedoDiff = std::max(dot(worldNormal, -lightDir), 0.f);
			auto reflectDir = this->reflectDir(m_direction, worldNormal);
			auto specularDiff = std::max(dot(worldNormal, -reflectDir), 0.f);

			auto albedoAns = m_color * albedoDiff * albedo;
			auto specularAns = m_specular * specularDiff;

			albedoAns *= insOffset;
			specularAns *= insOffset;

			return (albedoAns + specularAns) * m_intensity;
		}
	};
}