#pragma once

// glm
#include <glm/detail/type_vec1.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <glm/detail/type_mat2x3.hpp>
#include <glm/detail/type_mat2x4.hpp>
#include <glm/detail/type_mat3x2.hpp>
#include <glm/detail/type_mat3x3.hpp>
#include <glm/detail/type_mat3x4.hpp>
#include <glm/detail/type_mat4x2.hpp>
#include <glm/detail/type_mat4x3.hpp>
#include <glm/detail/type_mat4x4.hpp>

// nlohmann Json
#include <nlohmann/json.hpp>

namespace nlohmann
{

    ///
    template <glm::length_t L, typename T, glm::qualifier Q>
    struct adl_serializer<glm::vec<L, T, Q>>
    {
        ///
        template <size_t... Ns>
        static void Serialize(nlohmann::json& j, const glm::vec<L, T, Q>& value, std::index_sequence<Ns...>)
        {
            ((j[Ns] = value[Ns]), ...);
        }

        ///
        static void to_json(nlohmann::json& j, const glm::vec<L, T, Q>& value)
        {
            Serialize(j, value, std::make_index_sequence<L>{});
        }

        ///
        template <size_t... Ns>
        static void Deserialize(const nlohmann::json& j, glm::vec<L, T, Q>& value, std::index_sequence<Ns...>)
        {
            ((value[Ns] = j[Ns]), ...);
        }

        ///
        static void from_json(const nlohmann::json& j, glm::vec<L, T, Q>& value)
        {
            Deserialize(j, value, std::make_index_sequence<L>{});
        }
    };

    ///
    template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
    struct adl_serializer<glm::mat<C, R, T, Q>>
    {
        ///
        template <size_t... Ns>
        static void Serialize(nlohmann::json& j, const glm::mat<C, R, T, Q>& value, std::index_sequence<Ns...>)
        {
            ((j[Ns] = value[Ns]), ...);
        }

        ///
        static void to_json(nlohmann::json& j, const glm::mat<C, R, T, Q>& value)
        {
            Serialize(j, value, std::make_index_sequence<C>{});
        }

        ///
        template <size_t... Ns>
        static void Deserialize(const nlohmann::json& j, glm::mat<C, R, T, Q>& value, std::index_sequence<Ns...>)
        {
            ((value[Ns] = j[Ns]), ...);
        }

        ///
        static void from_json(const nlohmann::json& j, glm::mat<C, R, T, Q>& value)
        {
            Deserialize(j, value, std::make_index_sequence<C>{});
        }
    };

}
