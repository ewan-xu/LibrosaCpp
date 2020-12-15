/* ------------------------------------------------------------------
* Copyright (C) 2020 ewan xu<ewan_xu@outlook.com>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied.
* See the License for the specific language governing permissions
* and limitations under the License.
* -------------------------------------------------------------------
*/

#include "wavreader.h"
#include <librosa/librosa.h>

#include <iostream>
#include <vector>

#include <chrono>
#include <numeric>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
  void* h_x = wav_read_open("samples/p225_002.wav");

  int format, channels, sr, bits_per_sample;
  unsigned int data_length;
  int res = wav_get_header(h_x, &format, &channels, &sr, &bits_per_sample, &data_length);
  if (!res)
  {
    cerr << "get ref header error: " << res << endl;
    return -1;
  }

  int samples = data_length * 8 / bits_per_sample;
  std::vector<int16_t> tmp(samples);
  res = wav_read_data(h_x, reinterpret_cast<unsigned char*>(tmp.data()), data_length);
  if (res < 0)
  {
    cerr << "read wav file error: " << res << endl;
    return -1;
  }
  std::vector<float> x(samples);
  std::transform(tmp.begin(), tmp.end(), x.begin(),
    [](int16_t a) {
    return static_cast<float>(a) / 32767.f;
  });

  std::cout << "Sample rate: " << sr << "Hz" << std::endl;
  
  int n_fft = 400;
  int n_hop = 160;
  int n_mel = 40;
  int fmin = 80;
  int fmax = 7600;

  auto stft_start_time =  std::chrono::system_clock::now();
  std::vector<std::vector<std::complex<float>>> X = librosa::Feature::stft(x, n_fft, n_hop, "hann", true, "reflect");
  auto stft_end_time =  std::chrono::system_clock::now();
  auto stft_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stft_end_time - stft_start_time);
  std::cout<<"STFT runing time is "<< stft_duration.count() << "ms" <<std::endl;

  auto melspectrogram_start_time =  std::chrono::system_clock::now();
  std::vector<std::vector<float>> mels = librosa::Feature::melspectrogram(x, sr, n_fft, n_hop, "hann", true, "reflect", 2.f, n_mel, fmin, fmax);
  auto melspectrogram_end_time =  std::chrono::system_clock::now();
  auto melspectrogram_duration = std::chrono::duration_cast<std::chrono::milliseconds>(melspectrogram_end_time - melspectrogram_start_time);
  std::cout<<"Melspectrogram runing time is "<< melspectrogram_duration.count() << "ms" <<std::endl;
  
  assert(!mels.empty());
  std::cout<<"Verify the energy of melspectrogram features:"<<std::endl;
  std::cout<<"mel.dims: ["<<mels.size()<<","<<mels[0].size()<<"]"<<std::endl;
  std::cout<<"reduce_sum_in_times: "<<"[ ";
  for(int i = 0 ; i < mels.size(); i ++) {
	  float sum = std::accumulate(mels[i].begin(), mels[i].end(), 0.f, [](float& a, float& b) { return a+b;});
	  std::cout<<sum;
	  std::cout<<" ";
  }
  std::cout<<"]"<<std::endl;

  return 0;
}
