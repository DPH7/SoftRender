#pragma once
#include "globel.h"

namespace SoftRender
{
	enum ActionType {
		Distance,
		Angle,
		Scale,
	};

	class GameObject {
	public:
		mat4 m_model_mat = mat4(1.0);
		mat4 m_dis_mat = mat4(1.0);
		mat4 m_scale_mat = mat4(1.0);
		mat4 m_angle_mat = mat4(1.0);

		vec4 m_position;
		vec4 m_pre_position;

		/*修改*/
		vec3 m_move_dis = vec3();
		vec3 m_rotate_angle = vec3();
		vec3 m_scale = vec3(1.0);

	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(vec4 _pos) : m_position(_pos){
			m_pre_position = m_position;
		}

		/*修改*/
		void moveDistance(vec3 _dis) {
			m_move_dis = _dis;
			updateModelMat(ActionType::Distance);
		}

		void rotateAngle(vec3 _angle) {
			m_rotate_angle = _angle;
			updateModelMat(ActionType::Angle);
		}

		void changeScale(vec3 _scale) {
			m_scale = _scale;
			updateModelMat(ActionType::Scale);
		}

		/*获取自身模型矩阵*/
		void updateModelMat(ActionType _actionType) {
			m_dis_mat = mat4(1.0);
			m_scale_mat = mat4(1.0);
			m_angle_mat = mat4(1.0);
			m_position = m_pre_position;

			if (_actionType == ActionType::Distance) {
				m_rotate_angle = vec3();
				m_scale = vec3(1.0);
			}
			else if (_actionType == ActionType::Angle) {
				m_move_dis = vec3();
				m_scale = vec3(1.0);
			}
			else {
				m_move_dis = vec3();
				m_rotate_angle = vec3();
			}

			m_scale_mat = glm::scale(m_scale_mat, m_scale);

			m_dis_mat = glm::translate(m_dis_mat, m_move_dis);

			m_angle_mat = glm::rotate(m_angle_mat, glm::radians(m_rotate_angle.x), glm::vec3(1, 0, 0));
			m_angle_mat = glm::rotate(m_angle_mat, glm::radians(m_rotate_angle.y), glm::vec3(0, 1, 0));
			m_angle_mat = glm::rotate(m_angle_mat, glm::radians(m_rotate_angle.z), glm::vec3(0, 0, 1));

			m_model_mat = m_scale_mat * m_dis_mat * m_angle_mat * m_model_mat;

			m_position = m_model_mat * m_position;
		}
		mat4 getModelMat() {
			return m_model_mat;
		}
		mat4 getAngelMat() {
			return m_angle_mat;
		}
	};
}