# LibrosaCpp

LibrosaCpp is a c++ implemention of librosa using Eigen

# Authors
ewan xu <ewan_xu@outlook.com>

# About
similar with librosa, you can just use a single header [librosa.h](https://github.com/ewan-xu/LibrosaCpp/blob/main/librosa/librosa.h) to compute short-time fourier transform coefficients,mel spectrogram or mfcc

# Usage
1. copy the source directory 'librosa' to your project
2. add the source directory to your project include path
3. write a few lines of code

```cpp
#include <librosa/librosa.h>
```
```cpp
  int sr = 16000;
  int n_fft = 400;
  int n_hop = 160;
  std::string window = "hann";
  bool center = false;
  std::string pad_mode = "reflect";
  float power = 2.f;
  int n_mel = 40;
  int fmin = 80;
  int fmax = 7600;
  int n_mfcc = 20;
  bool norm = true;
  int type = 2;
  
  // compute short-time fourier transform coefficients
  std::vector<std::vector<std::complex<float>>> X = librosa::Feature::stft(x, n_fft, n_hop, window, center, pad_mode);
  // compute mel spectrogram
  std::vector<std::vector<float>> mels = librosa::Feature::melspectrogram(x, sr, n_fft, n_hop, window, center, pad_mode, power,n_mel, fmin, fmax);
  //compute mfcc
  std::vector<std::vector<float>> mfcc = librosa::Feature::mfcc(x, sr, n_fft, n_hop, window, center, pad_mode, power, n_mel, fmin, fmax, n_mfcc, norm, type);
```

# TODO
- other window function
- other dct type
- cepstral filtering

# Related projects
- [librosa](https://github.com/librosa/librosa)
- [eigen](https://gitlab.com/libeigen/eigen)
- [vo-amrwbenc](https://github.com/mstorsjo/vo-amrwbenc/blob/master/wavreader.h)
