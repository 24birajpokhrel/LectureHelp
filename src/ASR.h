#ifndef ASR_H
#define ASR_H

#include <string>
#include <vector>
#include "whisper.h"

class ASR {
    public:
    // load whisper model into this contructor
        ASR(const std::string& model_path);
    
    // Destructor to free loaded whisper model
        ~ASR();
    
    // Check if the model is loaded successfully
        bool isLoaded() const;
    // Return transcription of the audio file
        std::vector<std::string> transcribe(const float* pcm, int n_samples);
    
    private:
    // The loaded model context (nullptr if load failed)
        whisper_context* ctx;
    // Whisper settings
        whisper_full_params params;
    // tracks if context has been loaded successfully
        bool loaded;
};

#endif // ASR_H