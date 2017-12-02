[![Build Status](https://travis-ci.org/BykadorovR/AlgoGin.svg?branch=neuron)](https://travis-ci.org/BykadorovR/AlgoGin)
[![Coverage Status](https://coveralls.io/repos/github/BykadorovR/AlgoGin/badge.svg?branch=neuron)](https://coveralls.io/github/BykadorovR/AlgoGin?branch=neuron)

## Как построить и запустить решение:
1) Скачать репозиторий
2) Создать папку build в репозитории engine и запустить оттуда cmake ..
3) Открыть сгенерированный .sln файл и собрать проект в Release/Win32 (Windows)
4) Запустить в папке build комманду make .
5) Перейти в папку app и повторить процесс построения (Обязательно выполнять после сбора библиотеки, использовать Release/Win32 конфигурацию)
6) Запустить программу, передав ей переменные запуска: количество нейронов в скрытом слое, максимальную ошибку для останова, количество эпох, скорость обучения.
7) Дождаться завершения программы и увидеть похожий результат:<p>
**TRAIN**: Number equal: 59890, number not equal: 110<p>
**TEST**: Number equal: 9738, number not equal: 262
