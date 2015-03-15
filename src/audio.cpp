#include "include/audio.h"

audio::audio(std::string filename)
{
	pan = 0.0f;
	volume = 1.0f;
	pitch = 0.0f;
	loop = false;
	play_once = false;
	oshot = false;

	std::wstring fname(filename.begin(), filename.end());
	hm = BASS_StreamCreateFile(FALSE, fname.c_str(), NULL, NULL, BASS_STREAM_DECODE);
	hm = BASS_FX_TempoCreate(hm, BASS_FX_FREESOURCE);
}


audio::~audio()
{
	if (hm) BASS_SampleFree(hm);
}

void audio::play()
{
	if (loop)
		BASS_ChannelFlags(hm, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	else
		BASS_ChannelFlags(hm, NULL, BASS_SAMPLE_LOOP);

	if (play_once)
	{
		if (oshot)
		{
			BASS_ChannelSetAttribute(hm, BASS_ATTRIB_PAN, pan);
			BASS_ChannelSetAttribute(hm, BASS_ATTRIB_VOL, volume);
			BASS_ChannelSetAttribute(hm, BASS_ATTRIB_TEMPO_PITCH, pitch);
			BASS_ChannelPlay(hm, TRUE);
			playing = true;
			oshot = false;
		}
	}
	else
	{
		BASS_ChannelSetAttribute(hm, BASS_ATTRIB_PAN, pan);
		BASS_ChannelSetAttribute(hm, BASS_ATTRIB_VOL, volume);
		BASS_ChannelSetAttribute(hm, BASS_ATTRIB_TEMPO_PITCH, pitch);
		BASS_ChannelPlay(hm, TRUE);
		playing = true;
	}
}

void audio::pause()
{
	oshot = true;
	if (playing)
	{
		BASS_ChannelPause(hm);
		playing = false;
	}
}

void audio::stop()
{
	oshot = true;
	if (playing)
	{
		BASS_ChannelStop(hm);
		playing = false;
	}
}
