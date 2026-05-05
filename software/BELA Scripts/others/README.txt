README

Audio Onset Detection using Energy and Spectral Features
This project uses the Bela platform to detect audio onsets using energy and spectral features. The code is optimized for performance and logs onset events to a CSV file every second.
Features

    Audio onset detection using energy and spectral features
    Logging of onset events to a CSV file every second
    Configurable parameters for energy threshold, recording duration, and input gain
    Support for audio recording and saving to a WAV file
    Digital output pin activation after onset detection

Requirements

    Bela platform
    C++ compiler
    FFTW library for FFT calculations
    AudioFile library for audio recording and saving

Configuration
The project uses a configuration file config.txt to set the following parameters:

    energyThreshold: the threshold for detecting an onset
    recordAudio: whether to record audio or not (0 or 1)
    recordDuration: the duration of audio recording in seconds
    inputGain: the input gain for the microphones

Usage

    Compile the code using the Bela platform's compiler.
    Run the code on the Bela platform.
    The code will start detecting audio onsets and logging them to a CSV file every second.
    If audio recording is enabled, the code will save the recorded audio to a WAV file.

CSV File Format
The CSV file will contain the following columns:

    timestamp: the timestamp of the onset event in seconds
    detection: a flag indicating whether an onset was detected (1) or not (0)
    rms: the root mean square value of the audio signal
    freqContent: the frequency content of the audio signal

Notes

    The code uses a ring buffer to store onset events, which are logged to the CSV file every second.
    The code uses a digital output pin to activate after onset detection.
    The code supports audio recording and saving to a WAV file.

Troubleshooting

    If the code is not detecting onsets, check the energy threshold value and adjust it accordingly.
    If the code is not logging onset events to the CSV file, check the CSV file path and ensure that the file is not open in another program.
    If the code is not recording audio, check the audio recording settings and ensure that the audio input is working correctly.
    If the Compiler cant find "fftw3" add the following command to the “Make Parameters” section in the IDE's Settings: “LDLIBS=-lfftw3f”.
    This creates a link to the library, which should then allow the program to run. 
    If you want to go directly to the bela board to create a Makefile for the project, follow these steps:
    1.    Log in to bela as root
    	a.    Enter the following in a command prompt:
        	i.    ssh root@bela
       		ii.   Sometimes you may need to enter the IP address instead of “bela”. In that case, you might get an error saying you can’t access it. To fix this, go to 		      the following path: “C:\Users\‘yourName‘\.ssh”. ‘yourName’ should be your actual name. There, you’ll find a file named:                 “known_hosts”. 		      Find the line that starts with “bela.local” and delete only that line. Then log in again with ssh root@bela and press “yes” when prompted
        	iii.  The cmd line should now display the following: “root@bela:~#”
    2.    Next, navigate to your project
    	a.    Type `cd /root/Bela/“MyProject”`, where “MyProject” is the name of the project you're looking for
    	b.    You should now see `root@bela:~/Bela/projects/MyProject#`
    3.    Now open the Makefile
    	a.    To do this, enter “nano Makefile”
   	b.    You will now see either an empty or an existing Makefile. (In most cases, if nothing has been created in the project yet, it should be empty)

Important Note

    	Because of unoptimized memory usage for saving the .wav file we cant have a recording Duration higher than 300. We are working on it.

