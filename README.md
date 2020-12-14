# LibrosaCpp

LibrosaCpp is a c++ implemention of librosa using Eigen

# Authors
ewan xu <ewan_xu@outlook.com>

# About
similar with Eigen, you can just use a single header [librosa.h](https://github.com/ewan-xu/LibrosaCpp/blob/main/LibrosaCpp/librosa.h) to compute short-time fourier transform coefficients or mel spectrogram

# Usage
copy the source directory 'LibrosaCpp' to your project and write a few lines of code
```cpp
#include <LibrosaCpp/librosa.h>

  int n_fft = 400;
  int n_hop = 160;
  int n_mel = 40;
  int fmin = 80;
  int fmax = 7600;
  std::vector<std::vector<std::complex<float>>> X = librosa::Feature::stft(x, n_fft, n_hop, "hann", false, "reflect");
  std::vector<std::vector<float>> mels = librosa::Feature::melspectrogram(x, sr, n_fft, n_hop, "hann", false, "reflect", 2.f,n_mel, fmin, fmax);

```

# Related projects
- [librosa](https://github.com/librosa/librosa)
- [eigen](https://gitlab.com/libeigen/eigen)

