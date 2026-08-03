#include <cstdio>
#include <vector>
#include "whisper.h"
#include "llama.h"
#include "ASR.h"


int main() {
    printf("LectureHelp scaffold OK\n");

    // Load the whisper model
    ASR asr("extern/whisper.cpp/models/ggml-base.en.bin");

    if (!asr.isLoaded()) {
        fprintf(stderr, "Model failed to load, exiting.\n");
        return 1;
    }

    printf("Model loaded successfully.\n");

    // Build a fake PCM buffer: 2 seconds of silence at 16kHz
    int sample_rate = 16000;
    int duration_seconds = 2;
    int n_samples = sample_rate * duration_seconds;

    std::vector<float> fake_pcm(n_samples, 0.0f); // all zeros = silence

    // Run transcription on the fake buffer
    auto segments = asr.transcribe(fake_pcm.data(), fake_pcm.size());

    printf("Got %zu segments:\n", segments.size());
    for (const auto& s : segments) {
        printf("  %s\n", s.c_str());
    }

    return 0;
}
