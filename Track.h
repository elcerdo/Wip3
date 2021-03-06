#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"
#include "Array.h"
#include "Profile.h"

#include <vector>
#include <list>

struct Track
{
    Track(const Shader& shader_track, const Shader& shader_map, const std::string& texture);

    void
    draw(const glm::mat4& modelview) const;

    typedef Profile<21> TrackProfile;

    void
    beginBuild(const TrackProfile& profile);

    void
    appendStraight(const float length, const unsigned int subdiv=16);

    void
    appendTurn(const float angle, const float length, const unsigned int subdiv=16);

    void
    appendFlatWidthChange(const float end_width, const float length, const unsigned int subdiv=16);

    void
    appendPipeIn(const float width_total, const float width_flat, const float angle, const float length, const unsigned int subdiv=16);

    void
    appendPipeOut(const float width, const float length, const unsigned int subdiv=16);

    void
    appendTwist(const float angle, const float length, const unsigned int subdiv=16);

    void
    appendQuarter(const float angle, const float length, const unsigned int subdiv=16);

    void
    endBuild();

    glm::vec3
    trackPosition(const glm::vec2& position, const float height) const;

protected:

    unsigned int
    appendPoint(const glm::vec3& vertex, const glm::vec2& texture_coord);

    TrackProfile
    appendProfile(const TrackProfile& profile);

    void
    extrudeProfile(const TrackProfile& profile);

    TrackProfile last_profile;

    typedef std::vector<float> MapPositions;
    typedef std::vector<TrackProfile::Transforms> MapTransforms;
    MapPositions map_positions;
    MapTransforms map_transforms;

    Shader shader_track;
    Shader shader_map;
    Texture texture;

    typedef std::vector<glm::vec3> Vertices;
    typedef std::vector<glm::vec2> TextureCoords;
    typedef std::vector<glm::uvec3> Indexes;

    Vertices vertices_map;
    Vertices vertices;
    TextureCoords texture_coords;
    Indexes indexes;

    glm::mat4 transform_vertices;
    glm::mat3 transform_texture_coords;

    GLuint indexes_buffer;

};


