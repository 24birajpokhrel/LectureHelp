#include "ASR.h"
#include <cstdio>

ASR::ASR(const std::string& model_path){
    // Initialize whisper context
    ctx = whisper_init_from_file(model_path.c_str());
    loaded = (ctx != nullptr);

    if (loaded) {
        // Set default parameters
        params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    } else {
        fprintf(stderr, "Failed to load model from %s\n", model_path.c_str());
    }
}

//Destructor to free loaded whisper model
ASR::~ASR() {
    if (ctx != nullptr) {
        whisper_free(ctx);
    }
}

bool ASR::isLoaded() const {
    return loaded;
}

std::vector<std::string> ASR::transcribe(const float* pcm, int n_samples) {
    std::vector<std::string> results;

    if (!loaded) {
        fprintf(stderr, "ASR: transcribe() called but model is not loaded\n");
        return results;
    }

    int result = whisper_full(ctx, params, pcm, n_samples);

    if (result != 0) {
        fprintf(stderr, "ASR: whisper_full failed with code %d\n", result);
        return results;
    }

    int n_segments = whisper_full_n_segments(ctx);

    for (int i = 0; i < n_segments; ++i) {
        const char* text = whisper_full_get_segment_text(ctx, i);
        results.push_back(text);
    }

    return results;
}