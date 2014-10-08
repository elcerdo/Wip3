#include "Ship.h"

#include <glm/gtx/transform.hpp>

Ship::Ship(const Shader& shader, const std::string& texture, const glm::vec3& position, float acceleration, float rotationSpeed, float mass) :
    m_shader(shader), m_texture(texture),
    m_acceleration(acceleration), m_angle(0.0), m_roll(0.0), m_linearSpeed(0,0,0), m_mass(mass),
    m_rotationSpeed(rotationSpeed), m_position(position), m_orientation(100,0,0)
{
    float vertexTmp[] = {
         1.000000,-0.500000, 1.000000, -1.000000,-0.500000, 1.000000, -1.000000,-0.500000,-1.000000,
        -1.000000, 0.500000,-1.000000, -1.000000, 0.500000, 1.000000,  0.999999, 0.700000, 1.000001,
         3.000000, 0.000000,-0.999999,  1.000000, 0.700000,-0.999999,  2.000000, 0.600000,-0.699999,
         0.999999, 0.700000, 1.000001, -1.000000, 0.500000, 1.000000, -1.000000, 0.000000, 3.000000,
         1.000000,-0.500000,-1.000000, -1.000000,-0.500000,-1.000000, -1.000000, 0.000000,-3.000000,
         1.000000,-0.500000, 1.000000,  0.500000, 0.000000, 3.000000, -1.000000, 0.000000, 3.000000,
         1.000000, 0.700000,-0.999999,  0.500000, 0.000000,-3.000000, -1.000000, 0.000000,-3.000000,
         3.000000, 0.000000,-0.999999,  2.000000, 0.600000,-0.699999,  1.999999, 0.600000, 0.700001,
         3.000000, 0.000000,-0.999999,  0.500000, 0.000000,-3.000000,  1.000000, 0.700000,-0.999999,
         0.999999, 0.700000, 1.000001,  1.999999, 0.600000, 0.700001,  2.000000, 0.600000,-0.699999,
         0.500000, 0.000000, 3.000000,  3.000000, 0.000000, 1.000001,  0.999999, 0.700000, 1.000001,
         3.000000, 0.000000, 1.000001,  0.500000, 0.000000, 3.000000,  1.000000,-0.500000, 1.000000,
        -1.000000, 0.000000, 3.000000, -1.000000, 0.500000, 1.000000, -1.000000, 0.400000, 0.800000,
        -1.000000, 0.400000, 0.800000, -1.000000, 0.400000,-0.800000, -1.000000,-0.400000,-0.800000,
        -1.000000,-0.400000,-0.800000, -1.000000,-0.500000,-1.000000, -1.000000,-0.500000, 1.000000,
        -1.000000, 0.000000,-3.000000, -1.000000,-0.500000,-1.000000, -1.000000,-0.400000,-0.800000,
        -1.000000, 0.500000,-1.000000, -1.000000, 0.400000,-0.800000, -1.000000, 0.400000, 0.800000,
        -1.000000,-0.400000, 0.800000, -1.000000,-0.500000, 1.000000, -1.000000, 0.000000, 3.000000,
        -1.000000, 0.400000,-0.800000, -1.000000, 0.500000,-1.000000, -1.000000, 0.000000,-3.000000,
        -0.700000, 0.000000,-2.400000, -0.700000,-0.400000,-0.800000, -0.700000, 0.400000,-0.800000,
        -0.700000,-0.400000,-0.800000, -1.000000,-0.400000,-0.800000, -1.000000, 0.400000,-0.800000,
        -0.700000, 0.400000,-0.800000, -1.000000, 0.400000,-0.800000, -1.000000, 0.000000,-2.400000,
        -1.000000, 0.000000,-2.400000, -1.000000,-0.400000,-0.800000, -0.700000,-0.400000,-0.800000,
        -1.000000, 0.000000, 2.400000, -1.000000, 0.400000, 0.800000, -0.700000, 0.400000, 0.800000,
        -0.700000,-0.400000, 0.800000, -1.000000,-0.400000, 0.800000, -1.000000, 0.000000, 2.400000,
        -0.700000,-0.400000, 0.800000, -0.700000, 0.400000, 0.800000, -1.000000, 0.400000, 0.800000,
        -0.700000,-0.400000, 0.800000, -0.700000, 0.000000, 2.400000, -0.700000, 0.400000, 0.800000,
        -1.000000, 0.000000,-3.200000, -1.000000, 0.300000,-3.100000,  0.500000, 0.300000,-3.100000,
        -1.000000,-0.100000,-3.100000, -1.000000, 0.000000,-3.200000,  0.500000, 0.000000,-3.200000,
         0.500000, 0.000000, 3.200000, -1.000000, 0.000000, 3.200000, -1.000000,-0.100000, 3.100000,
         0.500000, 0.300000, 3.100000, -1.000000, 0.300000, 3.100000, -1.000000, 0.000000, 3.200000,
         0.800000, 0.000000,-3.100000,  0.500000,-0.100000,-3.100000,  0.500000, 0.000000,-3.200000,
        -1.000000, 0.000000,-3.000000, -1.000000,-0.100000,-3.100000,  0.500000,-0.100000,-3.100000,
         0.500000, 0.000000, 3.000000, -1.000000, 0.000000, 3.000000, -1.000000, 0.300000, 3.100000,
        -1.000000, 0.300000,-3.100000, -1.000000, 0.000000,-3.000000,  0.500000, 0.000000,-3.000000,
         0.500000, 0.000000,-3.000000,  0.800000, 0.000000,-3.100000,  0.500000, 0.300000,-3.100000,
        -1.000000, 0.300000,-3.100000, -1.000000, 0.000000,-3.200000, -1.000000,-0.100000,-3.100000,
         0.800000, 0.000000,-3.100000,  0.500000, 0.000000,-3.200000,  0.500000, 0.300000,-3.100000,
         0.800000, 0.000000,-3.100000,  0.500000, 0.000000,-3.000000,  0.500000,-0.100000,-3.100000,
         0.500000,-0.100000, 3.100000, -1.000000,-0.100000, 3.100000, -1.000000, 0.000000, 3.000000,
        -1.000000,-0.100000, 3.100000, -1.000000, 0.000000, 3.200000, -1.000000, 0.300000, 3.100000,
         0.800000, 0.000000, 3.100000,  0.500000, 0.000000, 3.200000,  0.500000,-0.100000, 3.100000,
         0.800000, 0.000000, 3.100000,  0.500000, 0.300000, 3.100000,  0.500000, 0.000000, 3.200000,
         0.800000, 0.000000, 3.100000,  0.500000, 0.000000, 3.000000,  0.500000, 0.300000, 3.100000,
         0.800000, 0.000000, 3.100000,  0.500000,-0.100000, 3.100000,  0.500000, 0.000000, 3.000000,
         0.999999, 0.700000, 1.000001,  3.000000, 0.000000, 1.000001,  1.999999, 0.600000, 0.700001,
         3.000000, 0.000000,-0.999999,  3.000000, 0.000000, 1.000001,  1.000000,-0.500000, 1.000000,
         0.500000, 0.000000,-3.000000,  3.000000, 0.000000,-0.999999,  1.000000,-0.500000,-1.000000,
         1.000000,-0.500000,-1.000000,  1.000000,-0.500000, 1.000000, -1.000000,-0.500000,-1.000000,
         1.000000, 0.700000,-0.999999, -1.000000, 0.500000,-1.000000,  0.999999, 0.700000, 1.000001,
         0.500000, 0.000000, 3.000000,  0.999999, 0.700000, 1.000001, -1.000000, 0.000000, 3.000000,
         0.500000, 0.000000,-3.000000,  1.000000,-0.500000,-1.000000, -1.000000, 0.000000,-3.000000,
        -1.000000,-0.500000, 1.000000,  1.000000,-0.500000, 1.000000, -1.000000, 0.000000, 3.000000,
        -1.000000, 0.500000,-1.000000,  1.000000, 0.700000,-0.999999, -1.000000, 0.000000,-3.000000,
         3.000000, 0.000000, 1.000001,  3.000000, 0.000000,-0.999999,  1.999999, 0.600000, 0.700001,
         1.000000, 0.700000,-0.999999,  0.999999, 0.700000, 1.000001,  2.000000, 0.600000,-0.699999,
        -1.000000, 0.000000, 2.400000, -1.000000, 0.000000, 3.000000, -1.000000, 0.400000, 0.800000,
        -1.000000,-0.400000, 0.800000, -1.000000, 0.400000, 0.800000, -1.000000,-0.400000,-0.800000,
        -1.000000,-0.400000, 0.800000, -1.000000,-0.400000,-0.800000, -1.000000,-0.500000, 1.000000,
        -1.000000, 0.000000,-2.400000, -1.000000, 0.000000,-3.000000, -1.000000,-0.400000,-0.800000,
        -1.000000, 0.500000, 1.000000, -1.000000, 0.500000,-1.000000, -1.000000, 0.400000, 0.800000,
        -1.000000, 0.000000, 2.400000, -1.000000,-0.400000, 0.800000, -1.000000, 0.000000, 3.000000,
        -1.000000, 0.000000,-2.400000, -1.000000, 0.400000,-0.800000, -1.000000, 0.000000,-3.000000,
        -0.700000, 0.400000,-0.800000, -0.700000,-0.400000,-0.800000, -1.000000, 0.400000,-0.800000,
        -0.700000, 0.000000,-2.400000, -0.700000, 0.400000,-0.800000, -1.000000, 0.000000,-2.400000,
        -0.700000, 0.000000,-2.400000, -1.000000, 0.000000,-2.400000, -0.700000,-0.400000,-0.800000,
        -0.700000, 0.000000, 2.400000, -1.000000, 0.000000, 2.400000, -0.700000, 0.400000, 0.800000,
        -0.700000, 0.000000, 2.400000, -0.700000,-0.400000, 0.800000, -1.000000, 0.000000, 2.400000,
        -1.000000,-0.400000, 0.800000, -0.700000,-0.400000, 0.800000, -1.000000, 0.400000, 0.800000,
         0.500000, 0.000000,-3.200000, -1.000000, 0.000000,-3.200000,  0.500000, 0.300000,-3.100000,
         0.500000,-0.100000,-3.100000, -1.000000,-0.100000,-3.100000,  0.500000, 0.000000,-3.200000,
         0.500000,-0.100000, 3.100000,  0.500000, 0.000000, 3.200000, -1.000000,-0.100000, 3.100000,
         0.500000, 0.000000, 3.200000,  0.500000, 0.300000, 3.100000, -1.000000, 0.000000, 3.200000,
         0.500000, 0.000000,-3.000000, -1.000000, 0.000000,-3.000000,  0.500000,-0.100000,-3.100000,
         0.500000, 0.300000, 3.100000,  0.500000, 0.000000, 3.000000, -1.000000, 0.300000, 3.100000,
         0.500000, 0.300000,-3.100000, -1.000000, 0.300000,-3.100000,  0.500000, 0.000000,-3.000000,
        -1.000000, 0.000000,-3.000000, -1.000000, 0.300000,-3.100000, -1.000000,-0.100000,-3.100000,
         0.500000, 0.000000, 3.000000,  0.500000,-0.100000, 3.100000, -1.000000, 0.000000, 3.000000,
        -1.000000, 0.000000, 3.000000, -1.000000,-0.100000, 3.100000, -1.000000, 0.300000, 3.100000,
         1.000000,-0.500000,-1.000000,  3.000000, 0.000000,-0.999999,  1.000000,-0.500000, 1.000000
    };

    float coordTextureTmp[] = {
        0.454381,0.781965, 0.454381,0.595359, 0.640988,0.595359,
        0.452763,0.185726, 0.642743,0.185726, 0.642744,0.375707,
        0.452763,0.565688, 0.452763,0.375707, 0.481260,0.470698,
        0.642744,0.375707, 0.642743,0.185726, 0.832724,0.185726,
        0.640988,0.781965, 0.640988,0.595359, 0.827594,0.595359,
        0.454381,0.781965, 0.267774,0.735314, 0.267774,0.595359,
        0.452763,0.375707, 0.262782,0.328212, 0.262782,0.185726,
        0.452763,0.565688, 0.481260,0.470698, 0.614246,0.470697,
        0.452763,0.565688, 0.262782,0.328212, 0.452763,0.375707,
        0.642744,0.375707, 0.614246,0.470697, 0.481260,0.470698,
        0.832724,0.328212, 0.642744,0.565688, 0.642744,0.375707,
        0.454381,0.968572, 0.267774,0.735314, 0.454381,0.781965,
        0.266793,0.095536, 0.460359,0.047145, 0.479715,0.056823,
        0.479715,0.056823, 0.634567,0.056823, 0.634567,0.134249,
        0.634567,0.134249, 0.653924,0.143928, 0.460358,0.143928,
        0.847489,0.095536, 0.653924,0.143928, 0.634567,0.134249,
        0.653924,0.047145, 0.634567,0.056823, 0.479715,0.056823,
        0.479715,0.134249, 0.460358,0.143928, 0.266793,0.095536,
        0.634567,0.056823, 0.653924,0.047145, 0.847489,0.095536,
        0.789420,0.095536, 0.634567,0.134249, 0.634567,0.056823,
        0.216525,0.098396, 0.239695,0.098467, 0.239505,0.160253,
        0.169238,0.160111, 0.146069,0.160182, 0.145690,0.036610,
        0.192408,0.036539, 0.192787,0.160110, 0.169618,0.160182,
        0.193166,0.160182, 0.192787,0.036610, 0.215957,0.036539,
        0.145311,0.160182, 0.122141,0.160110, 0.122520,0.036539,
        0.216525,0.098396, 0.216336,0.036610, 0.239505,0.036539,
        0.479715,0.134249, 0.324863,0.095536, 0.479715,0.056823,
        0.205008,0.456626, 0.185588,0.452171, 0.185290,0.247637,
        0.224422,0.456598, 0.205008,0.456626, 0.204710,0.252093,
        0.175364,0.688978, 0.175639,0.485477, 0.184317,0.488137,
        0.131954,0.688919, 0.132229,0.485418, 0.175639,0.485477,
        0.214356,0.210051, 0.224124,0.252065, 0.204710,0.252093,
        0.176612,0.210110, 0.185290,0.212770, 0.185015,0.416272,
        0.203737,0.527460, 0.204035,0.731993, 0.184615,0.727538,
        0.133202,0.210051, 0.176612,0.210110, 0.176337,0.413611,
        0.176337,0.413611, 0.171938,0.456292, 0.132927,0.413553,
        0.224422,0.262136, 0.224439,0.218726, 0.241806,0.210051,
        0.214356,0.210051, 0.204710,0.252093, 0.185290,0.247637,
        0.171938,0.456292, 0.176337,0.413611, 0.185015,0.416272,
        0.223151,0.527431, 0.223449,0.731965, 0.204035,0.731993,
        0.232124,0.485418, 0.249491,0.494093, 0.249508,0.537503,
        0.170965,0.731659, 0.175364,0.688978, 0.184042,0.691638,
        0.170965,0.731659, 0.131954,0.688919, 0.175364,0.688978,
        0.213383,0.485418, 0.203737,0.527460, 0.184317,0.523004,
        0.213383,0.485418, 0.223151,0.527431, 0.203737,0.527460,
        0.642744,0.375707, 0.642744,0.565688, 0.614246,0.470697,
        0.640988,0.968572, 0.454381,0.968572, 0.454381,0.781965,
        0.827594,0.735314, 0.640988,0.968572, 0.640988,0.781965,
        0.640988,0.781965, 0.454381,0.781965, 0.640988,0.595359,
        0.452763,0.375707, 0.452763,0.185726, 0.642744,0.375707,
        0.832724,0.328212, 0.642744,0.375707, 0.832724,0.185726,
        0.827594,0.735314, 0.640988,0.781965, 0.827594,0.595359,
        0.454381,0.595359, 0.454381,0.781965, 0.267774,0.595359,
        0.452763,0.185726, 0.452763,0.375707, 0.262782,0.185726,
        0.642744,0.565688, 0.452763,0.565688, 0.614246,0.470697,
        0.452763,0.375707, 0.642744,0.375707, 0.481260,0.470698,
        0.324863,0.095536, 0.266793,0.095536, 0.479715,0.056823,
        0.479715,0.134249, 0.479715,0.056823, 0.634567,0.134249,
        0.479715,0.134249, 0.634567,0.134249, 0.460358,0.143928,
        0.789420,0.095536, 0.847489,0.095536, 0.634567,0.134249,
        0.460359,0.047145, 0.653924,0.047145, 0.479715,0.056823,
        0.324863,0.095536, 0.479715,0.134249, 0.266793,0.095536,
        0.789420,0.095536, 0.634567,0.056823, 0.847489,0.095536,
        0.216336,0.160182, 0.216525,0.098396, 0.239505,0.160253,
        0.168859,0.036539, 0.169238,0.160111, 0.145690,0.036610,
        0.169238,0.036610, 0.192408,0.036539, 0.169618,0.160182,
        0.216336,0.160110, 0.193166,0.160182, 0.215957,0.036539,
        0.145690,0.036610, 0.145311,0.160182, 0.122520,0.036539,
        0.239695,0.098325, 0.216525,0.098396, 0.239505,0.036539,
        0.204710,0.252093, 0.205008,0.456626, 0.185290,0.247637,
        0.224124,0.252065, 0.224422,0.456598, 0.204710,0.252093,
        0.184042,0.691638, 0.175364,0.688978, 0.184317,0.488137,
        0.175364,0.688978, 0.131954,0.688919, 0.175639,0.485477,
        0.176337,0.413611, 0.176612,0.210110, 0.185015,0.416272,
        0.184317,0.523004, 0.203737,0.527460, 0.184615,0.727538,
        0.132927,0.413553, 0.133202,0.210051, 0.176337,0.413611,
        0.250481,0.227418, 0.224422,0.262136, 0.241806,0.210051,
        0.203737,0.527460, 0.223151,0.527431, 0.204035,0.731993,
        0.223449,0.502785, 0.232124,0.485418, 0.249508,0.537503,
        0.640988,0.781965, 0.640988,0.968572, 0.454381,0.781965
    };

    float normalsTmp[] = {
         0.000000,-1.000000, 0.000000,  0.000000,-1.000000, 0.000000,  0.000000,-1.000000, 0.000000,
        -0.099500, 0.995000,-0.000000, -0.099500, 0.995000,-0.000000, -0.099500, 0.995000,-0.000000,
         0.259700, 0.741900,-0.618200,  0.259700, 0.741900,-0.618200,  0.259700, 0.741900,-0.618200,
        -0.096600, 0.965600, 0.241400, -0.096600, 0.965600, 0.241400, -0.096600, 0.965600, 0.241400,
         0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,
        -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500,
         0.000000, 0.943900,-0.330400,  0.000000, 0.943900,-0.330400,  0.000000, 0.943900,-0.330400,
         0.514500, 0.857500, 0.000000,  0.514500, 0.857500, 0.000000,  0.514500, 0.857500, 0.000000,
         0.305300, 0.872400,-0.381700,  0.305300, 0.872400,-0.381700,  0.305300, 0.872400,-0.381700,
         0.099500, 0.995000, 0.000000,  0.099500, 0.995000, 0.000000,  0.099500, 0.995000, 0.000000,
         0.305300, 0.872400, 0.381700,  0.305300, 0.872400, 0.381700,  0.305300, 0.872400, 0.381700,
         0.232100,-0.928400, 0.290100,  0.232100,-0.928400, 0.290100,  0.232100,-0.928400, 0.290100,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.000000, 0.000000,-1.000000,  0.000000, 0.000000,-1.000000,  0.000000, 0.000000,-1.000000,
        -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500,
        -0.000000, 0.970100, 0.242500, -0.000000, 0.970100, 0.242500, -0.000000, 0.970100, 0.242500,
         0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,
         0.000000, 0.970100,-0.242500,  0.000000, 0.970100,-0.242500,  0.000000, 0.970100,-0.242500,
        -0.000000, 0.000000, 1.000000, -0.000000, 0.000000, 1.000000, -0.000000, 0.000000, 1.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,
         0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,
        -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100,
        -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700,
         0.229400,-0.688200,-0.688200,  0.229400,-0.688200,-0.688200,  0.229400,-0.688200,-0.688200,
        -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100,
         0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,
        -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700,
         0.301500, 0.301500, 0.904500,  0.301500, 0.301500, 0.904500,  0.301500, 0.301500, 0.904500,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.301500, 0.301500,-0.904500,  0.301500, 0.301500,-0.904500,  0.301500, 0.301500,-0.904500,
         0.229400,-0.688200, 0.688200,  0.229400,-0.688200, 0.688200,  0.229400,-0.688200, 0.688200,
         0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.229400,-0.688200, 0.688200,  0.229400,-0.688200, 0.688200,  0.229400,-0.688200, 0.688200,
         0.301500, 0.301500, 0.904500,  0.301500, 0.301500, 0.904500,  0.301500, 0.301500, 0.904500,
         0.301500, 0.301500,-0.904500,  0.301500, 0.301500,-0.904500,  0.301500, 0.301500,-0.904500,
         0.229400,-0.688200,-0.688200,  0.229400,-0.688200,-0.688200,  0.229400,-0.688200,-0.688200,
         0.259700, 0.741900, 0.618200,  0.259700, 0.741900, 0.618200,  0.259700, 0.741900, 0.618200,
         0.242500,-0.970100, 0.000000,  0.242500,-0.970100, 0.000000,  0.242500,-0.970100, 0.000000,
         0.232100,-0.928400,-0.290100,  0.232100,-0.928400,-0.290100,  0.232100,-0.928400,-0.290100,
         0.000000,-1.000000, 0.000000,  0.000000,-1.000000, 0.000000,  0.000000,-1.000000, 0.000000,
        -0.099500, 0.995000,-0.000000, -0.099500, 0.995000,-0.000000, -0.099500, 0.995000,-0.000000,
        -0.000000, 0.943900, 0.330400, -0.000000, 0.943900, 0.330400, -0.000000, 0.943900, 0.330400,
         0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,
        -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500,
        -0.096600, 0.965600,-0.241400, -0.096600, 0.965600,-0.241400, -0.096600, 0.965600,-0.241400,
         0.514500, 0.857500, 0.000000,  0.514500, 0.857500, 0.000000,  0.514500, 0.857500, 0.000000,
         0.099500, 0.995000, 0.000000,  0.099500, 0.995000, 0.000000,  0.099500, 0.995000, 0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.000000, 0.000000,-1.000000,  0.000000, 0.000000,-1.000000,  0.000000, 0.000000,-1.000000,
        -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500, -0.000000,-0.970100, 0.242500,
        -0.000000, 0.970100, 0.242500, -0.000000, 0.970100, 0.242500, -0.000000, 0.970100, 0.242500,
         0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,  0.000000,-0.970100,-0.242500,
         0.000000, 0.970100,-0.242500,  0.000000, 0.970100,-0.242500,  0.000000, 0.970100,-0.242500,
        -0.000000, 0.000000, 1.000000, -0.000000, 0.000000, 1.000000, -0.000000, 0.000000, 1.000000,
         0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,
         0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,
        -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100,
        -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700,
        -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100, -0.000000,-0.707100, 0.707100,
         0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,  0.000000, 0.316200,-0.948700,
        -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700, -0.000000, 0.316200, 0.948700,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,  0.000000,-0.707100,-0.707100,
        -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000, -1.000000, 0.000000,-0.000000,
         0.242500,-0.970100, 0.000000,  0.242500,-0.970100, 0.000000,  0.242500,-0.970100, 0.000000
    };

    for(int i(0); i<720; i++)
    {
        m_vertex[i] = vertexTmp[i];
        m_normals[i] = normalsTmp[i];
    }
    for(int i(0); i<480; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}

void Ship::draw(const glm::mat4& modelview)
{
    glm::mat4 modelview_local = modelview;
    modelview_local = glm::translate(modelview_local, m_position);
    modelview_local = glm::rotate(modelview_local, glm::radians(m_angle), glm::vec3(0,-1,0));
    modelview_local = glm::rotate(modelview_local, glm::radians(m_roll), glm::vec3(1,0,0));

    m_shader.setUniform("modelview", modelview_local);

    glUseProgram(m_shader.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, m_texture.getID());
    glDrawArrays(GL_TRIANGLES, 0, 240);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

void Ship::control(Input const& input)
{
    float acceleration(0.0);
    float frictionFactor(m_mass / 100000.0);
    float stabilization(0.05);
    glm::vec3 friction(0,0,0);

    if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W))
        acceleration = m_acceleration;

    if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S))
        frictionFactor = m_mass / 30000.0;

    if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A))
    {
        m_angle -= m_rotationSpeed;
        m_roll -= 0.8;
    }

    if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D))
    {
        m_angle += m_rotationSpeed;
        m_roll += 0.8;
    }

    if(!(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W)) && !(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S)))
        frictionFactor = m_mass / 50000.0;

    friction.x = -m_linearSpeed.x * frictionFactor;
    friction.y = -m_linearSpeed.y * frictionFactor;
    friction.z = -m_linearSpeed.z * frictionFactor;

    if(m_angle < 0.0)
        m_angle += 360.0;
    if(m_angle > 360.0)
        m_angle -= 360.0;

    m_roll = m_roll - stabilization*m_roll;

    glm::vec3 movement(Ship::movement(acceleration));
    m_linearSpeed += movement + friction;
    m_position += m_linearSpeed;
    orientate();
}

glm::vec3 Ship::movement(float acceleration) const
{
    float angleRad = glm::radians(m_angle);
    glm::vec3 movement;

    movement.x = cos(angleRad) * acceleration;
    movement.y = 0;
    movement.z = sin(angleRad) * acceleration;

    return movement;
}

void Ship::orientate()
{
    float angleRad = glm::radians(m_angle);
    glm::vec3 linearSpeedNorm(glm::normalize(m_linearSpeed));

    m_orientation.x = cos(angleRad) * 100;
    m_orientation.y = 0;
    m_orientation.z = sin(angleRad) * 100;

    m_orientation += m_position;
}

glm::vec3 Ship::getPosition() const
{
    return m_position;
}

glm::vec3 Ship::getOrientation() const
{
    return m_orientation;
}

glm::vec3 Ship::getLinearSpeed() const
{
    return m_linearSpeed;
}
