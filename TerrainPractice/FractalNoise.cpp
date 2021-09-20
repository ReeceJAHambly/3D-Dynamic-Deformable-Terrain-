//I do not claim ownership or development of any code within this class

#include "FractalNoise.h"

FractalNoise::FractalNoise() {
	m_perlinSource = new Perlin();

	m_octaves = 6;//6;
	m_lacunarity = 0.25f; //0.25
	m_persistence = 1.0f; // 1.0
	m_baseFrequency = (float)0.1; // 0.1
	m_baseAmplitude = 5.5f; // 5.5
}

FractalNoise::~FractalNoise() {
	delete m_perlinSource;
}

float FractalNoise::noise(float sample_x, float sample_y, float sample_z) {
	float sum = 0;
	float freq = m_baseFrequency;
	float amp = m_baseAmplitude;

	for (int i = 0; i < m_octaves; ++i) {
		sum += m_perlinSource->noise(sample_x*freq, sample_y*freq, sample_z*freq)*amp;

		freq *= m_lacunarity;
		amp *= m_persistence;
	}

	return sum;
}

void FractalNoise::setOctaves(int o) {
	if (o > 0) {
		m_octaves = o;
	}
}

void FractalNoise::setPersistence(float p) {
	m_persistence = p;
}

void FractalNoise::setLacunarity(float l) {
	m_lacunarity = l;
}

void FractalNoise::setBaseFrequency(float f) {
	m_baseFrequency = f;
}

void FractalNoise::setBaseAmplitude(float a) {
	m_baseAmplitude = a;
}