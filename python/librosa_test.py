"""
------------------------------------------------------------------
Copyright (C) 2020 SunAriesCN <281614085@qq.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
express or implied.
See the License for the specific language governing permissions
and limitations under the License.
-------------------------------------------------------------------
"""

# coding: utf-8

import os
import numpy as np

import tslearn
import librosa
import librosa.display

import glob
import tslearn.metrics

n_fft = 400
n_hop = 160
n_mel = 40
fmin = 80
fmax = 7600 

wave_data_path = "../samples/p225_002.wav"
wave_data, sample_rate = librosa.load(wave_data_path, 16000)
print(f"Sample rate: {sample_rate}")
wave_data = librosa.to_mono(wave_data)
mfcc = librosa.feature.melspectrogram(y=wave_data, sr=sample_rate, n_mels=n_mel,
        n_fft=n_fft, hop_length=n_hop, power=2., fmin=fmin, fmax=fmax)

mfcc.shape

mfcc_sum = np.sum(mfcc, axis=0)
mfcc_sum.shape
print(mfcc_sum)


