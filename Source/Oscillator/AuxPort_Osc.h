#ifndef AuxPort_OSC_H
#define AuxPort_OSC_H


namespace AuxPort
{

	typedef unsigned int uint32;
	typedef int int32;
	typedef unsigned long long int uint64;
	typedef long long int int64;
	
	class Sawtooth
	{
	public:
		Sawtooth() = default;
		~Sawtooth() = default;
		Sawtooth(const Sawtooth& oscillator) = default;
		void setSampleRate(const uint32& sampleRate)
		{
			if (this->sampleRate != sampleRate)
			{
				this->sampleRate = sampleRate;
				stop();
                
			}
			
		}

		void setFrequency(const float& frequency)
		{
			indexIncrement = frequency / this->sampleRate;
		}

		float getSample()
		{
			if (isPlaying())
			{
				if (mod >= 1.0)
                    mod = mod - 1.0;
                sample = 2.0 * mod - 1.0;
                mod += indexIncrement;
                return sample;
			}
		}

		void stop()
		{
			indexIncrement = 0;
			mod = 0;
		}

		bool isPlaying()
		{
			return indexIncrement != 0;
		}

	private:
		float indexIncrement = 0;
		float mod = 0;
		float sample = 0;
		uint32 sampleRate = 44100;

	};

class sinewave
{
public:
    sinewave() = default;
    ~sinewave() = default;
    sinewave(const sinewave& oscillator) = default;
    void setSampleRate(const uint32& sampleRate)
    {
        if (this->sampleRate != sampleRate)
        {
            this->sampleRate = sampleRate;
            stop();
        }
        
    }

    void setFrequency(const float& frequency)
    {
        indexIncrement = frequency / this->sampleRate;
    }

    float getSample()
    {
        if (isPlaying())
        {
            if (mod >= 1.0)
                mod = mod - 1.0;
            sample = sin(mod * 3.14159265358979323846264338327 * 2);
            mod += indexIncrement;
            return sample;
        }
    }

    void stop()
    {
        indexIncrement = 0;
        mod = 0;
    }

    bool isPlaying()
    {
        return indexIncrement != 0;
    }

private:
    float indexIncrement = 0;
    float mod = 0;
    float sample = 0;
    uint32 sampleRate = 44100;

};

class squarewave
    {
    public:
        squarewave() = default;
        ~squarewave() = default;
        squarewave(const squarewave& oscillator) = default;
        void setSampleRate(const uint32& sampleRate)
        {
            if (this->sampleRate != sampleRate)
            {
                this->sampleRate = sampleRate;
                stop();
                
            }
            
        }

        void setFrequency(const float& frequency)
        {
            indexIncrement = frequency / this->sampleRate;
        }

        float getSample()
        {
            if (isPlaying())
            {
                if (mod >= 1.0)
                    mod = mod - 1.0;
                sample = mod > 0.5 ? -1.0 : +1.0;
                mod += indexIncrement;
                return sample;
            }
        }

        void stop()
        {
            indexIncrement = 0;
            mod = 0;
        }

        bool isPlaying()
        {
            return indexIncrement != 0;
        }

    private:
        float indexIncrement = 0;
        float mod = 0;
        float sample = 0;
        uint32 sampleRate = 44100;

    };

class trianglewave
{
public:
    trianglewave() = default;
    ~trianglewave() = default;
    trianglewave(const trianglewave& oscillator) = default;
    void setSampleRate(const uint32& sampleRate)
    {
        if (this->sampleRate != sampleRate)
        {
            this->sampleRate = sampleRate;
            stop();
        }
        
    }

    void setFrequency(const float& frequency)
    {
        indexIncrement = frequency / this->sampleRate;
    }

    float getSample()
    {
        if (isPlaying())
        {
            if (mod >= 1.0)
                mod -= 1.0;
            sample = 2.0 * fabs(2.0 * mod - 1.0) - 1.0;
            mod += indexIncrement;
            return sample;
        }
    }

    void stop()
    {
        indexIncrement = 0;
        mod = 0;
    }

    bool isPlaying()
    {
        return indexIncrement != 0;
    }

private:
    float indexIncrement = 0;
    float mod = 0;
    float sample = 0;
    uint32 sampleRate = 44100;

};


}



#endif


