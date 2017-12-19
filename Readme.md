[![Build Status](https://travis-ci.org/BykadorovR/AlgoGin.svg?branch=neuron)](https://travis-ci.org/BykadorovR/AlgoGin)
[![Coverage Status](https://coveralls.io/repos/github/BykadorovR/AlgoGin/badge.svg?branch=neuron)](https://coveralls.io/github/BykadorovR/AlgoGin?branch=neuron)

## Как построить и запустить решение:
1) Скачать репозиторий
2) Создать папку \_build в репозитории engine и запустить оттуда cmake ..
3) Открыть сгенерированный .sln файл и собрать проект в Release/Win32 (Windows)
4) Перейти в папку app и повторить процесс построения (Обязательно выполнять после сбора библиотеки, использовать Release/Win32 конфигурацию)
5) Запустить программу, передав ей переменные запуска: количество нейронов в скрытом слое, максимальную ошибку для останова, количество эпох, скорость обучения. \
Желательно запускать из VisualStudio предварительно указав параметры запуска в Debugging->Command Arguments поле, например, 300 0.001 20 0.01. Или переместить бинарный файл из папки app/build/Release в папку app/build и запустить с теми же параметрами.
6) Дождаться завершения программы и увидеть похожий результат:</p>
**TRAIN**: Number equal: 59890, number not equal: 110</br>
**TEST**: Number equal: 9738, number not equal: 262
