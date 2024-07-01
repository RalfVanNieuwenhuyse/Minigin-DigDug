#include "TrashTheCache.h"

#include "imgui.h"
#include "imgui_plot.h"
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include <atomic>

dae::TrashTheCache::TrashTheCache(GameObject* owner)
	:Component(owner)
{
}

void dae::TrashTheCache::RenderImGui()
{
	RenderExercise1();
	RenderExercise2();
}

void dae::TrashTheCache::PlotTimes(const std::vector<float>& times, const char* label)
{
	ImColor color{ 1.f, 0.f, 0.f, 1.f };

	auto maxVal = *std::max_element(begin(times), end(times));
	auto minVal = *std::min_element(begin(times), end(times));

	ImGui::PlotConfig conf;
	conf.values.ys = times.data();
	conf.values.xs = TIME_STEPS.data();
	conf.values.count = static_cast<int>(times.size() + 1);
	conf.values.color = color;

	conf.scale.min = minVal;
	conf.scale.max = maxVal;

	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";

	conf.grid_x.show = true;
	conf.grid_y.show = true;

	conf.frame_size = ImVec2(200, 200);
	conf.line_thickness = 2.f;

	ImGui::Plot(label, conf);
}

void dae::TrashTheCache::DoublePlot(const std::vector<float>& times1, const std::vector<float>& times2, const char* label)
{
	const float maxVal = std::max(*std::max_element(begin(times1), end(times1)), *std::max_element(begin(times2), end(times2)));
	const float minVal = std::min(*std::min_element(begin(times1), end(times1)), *std::min_element(begin(times2), end(times2)));

	const int nrOfPoints = static_cast<int>(std::max(times1.size() + 1, times2.size() + 1));
	const float* timingsGroup[2] = { times1.data(), times2.data() };

	ImColor color1{ 1.f, 0.f, 0.f, 1.f };
	ImColor color2{ 1.f, 1.f, 0.f, 1.f };
	const ImU32 colors[2] = { color1, color2 };

	ImGui::PlotConfig conf;
	conf.values.colors = colors;
	conf.values.ys_list = timingsGroup;
	conf.values.ys_count = 2;
	conf.values.xs = TIME_STEPS.data();
	conf.values.count = nrOfPoints;
	conf.scale.min = minVal;
	conf.scale.max = maxVal;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.grid_y.size = maxVal / 10.0f;
	conf.frame_size = ImVec2(200, 200);
	conf.line_thickness = 2.f;

	ImGui::Plot(label, conf);
}

void dae::TrashTheCache::RenderExercise1()
{
	ImGui::Begin("Exercise 1", nullptr);

	ImGui::InputInt("samples", &m_Ex1Samples);

	if (ImGui::Button("Trash the cash")&& !m_exercise1IsRunning){
		m_exercise1IsRunning = true;
		std::thread t(&TrashTheCache::Exercise1, this);
		t.detach();
	}

	if (m_Ex1Times.size() > 0)
	{
		PlotTimes(m_Ex1Times, "Ex1");
	}

	ImGui::End();
}

void dae::TrashTheCache::Exercise1()
{
	m_Ex1Times.clear();

	std::map<int, std::vector<float>> timings{};

	int* arpoint = new int[ARRAY_SIZE] {};

	for (int j = 0; j < m_Ex1Samples; j++)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < ARRAY_SIZE; i += stepsize)
			{
				arpoint[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			
			timings[stepsize].push_back(static_cast<float>(elapsedTime));
			
		}
	}

	delete[] arpoint;

	HandleTimings(timings, m_Ex1Times);
	m_exercise1IsRunning = false;
}

void dae::TrashTheCache::RenderExercise2()
{
	ImGui::Begin("Excersise 2", nullptr);

	ImGui::InputInt("samples", &m_Ex2Samples);

	if (ImGui::Button("Trash the cash GameObjects") && !m_exercise2IsRunning)
	{		
		m_exercise2IsRunning = true;
		std::thread t(&TrashTheCache::GameObjects3D, this);
		t.detach();
	}

	if (m_Ex2Times.size() > 0)
		PlotTimes(m_Ex2Times, "GameObjects3D");

	ImGui::Separator();

	if (ImGui::Button("Trash the cash GameObjectAlts") && !m_exercise2AltIsRunning)
	{		
		m_exercise2AltIsRunning = true;
		std::thread t(&TrashTheCache::GameObjects3DAlt, this);
		t.detach();
	}

	if (m_Ex2AltTimes.size() > 0)
		PlotTimes(m_Ex2AltTimes, "GameObjects3DAlt");	

	if (m_Ex2Times.size() > 0 && m_Ex2AltTimes.size() > 0)
	{
		ImGui::SeparatorText("Combined");
		DoublePlot(m_Ex2Times, m_Ex2AltTimes, "double plot");
	}

	ImGui::End();
}

void dae::TrashTheCache::GameObjects3D()
{
	m_Ex2Times.clear();

	GameObject3D* GameObjeArrpoint = new GameObject3D[ARRAY_SIZE]{};
	std::map<int, std::vector<float>> timings{};
	for (int j = 0; j < m_Ex2Samples; j++)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < ARRAY_SIZE; i += stepsize)
			{
				GameObjeArrpoint[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			timings[stepsize].push_back(static_cast<float>(elapsedTime));
		}
	}
	delete[] GameObjeArrpoint;

	HandleTimings(timings, m_Ex2Times);
	m_exercise2IsRunning = false;
}

void dae::TrashTheCache::GameObjects3DAlt()
{
	m_Ex2AltTimes.clear();
	GameObject3DAlt* GameObjeArrpoint = new GameObject3DAlt[ARRAY_SIZE]{};
	std::map<int, std::vector<float>> timings{};
	for (int j = 0; j < m_Ex2Samples; j++)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < ARRAY_SIZE; i += stepsize)
			{
				GameObjeArrpoint[i].ID *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			timings[stepsize].push_back(static_cast<float>(elapsedTime));
		}
	}
	delete[] GameObjeArrpoint;
	HandleTimings(timings, m_Ex2AltTimes);
	m_exercise2AltIsRunning = false;
}

void dae::TrashTheCache::HandleTimings(const std::map<int, std::vector<float>>& timings, std::vector<float>& resultVec)
{
	for (auto& timing : timings)
	{
		if (timing.second.size() <= 2) return;

		std::vector<float> sortedVec = timing.second;
		std::sort(sortedVec.begin(), sortedVec.end());

		sortedVec.erase(sortedVec.begin());
		sortedVec.pop_back();

		float sum{ 0.0f };

		for (float value : sortedVec) {
			sum += value;
		}

		resultVec.push_back(sum / static_cast<float>(sortedVec.size()));
	}
}