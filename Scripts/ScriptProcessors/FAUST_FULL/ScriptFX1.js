 function prepareToPlay(sampleRate, blockSize)
{
	
}
 function processBlock(channels)
{
    local numSamples = channels[0].length;
    local pitchRatio = calculatePitchShift(pitchShiftSemitones);
    
    for (i = 0; i < numSamples; i++)
    {
        // Store the current sample in our pitch buffer
        pitchBufferL[writeIndex] = channels[0][i];
        pitchBufferR[writeIndex] = channels[1][i];
        
        // Read from pitch buffer with pitch shifting
        local readIndexFloat = readIndex * pitchRatio;
        local readIndexInt = Math.floor(readIndexFloat);
        local frac = readIndexFloat - readIndexInt;
        
        local idx1 = readIndexInt % BUFFER_LENGTH;
        local idx2 = (readIndexInt + 1) % BUFFER_LENGTH;
        
        // Linear interpolation
        channels[0][i] = pitchBufferL[idx1] * (1 - frac) + pitchBufferL[idx2] * frac;
        channels[1][i] = pitchBufferR[idx1] * (1 - frac) + pitchBufferR[idx2] * frac;
        
        writeIndex = (writeIndex + 1) % BUFFER_LENGTH;
        readIndex = (readIndex + 1) % BUFFER_LENGTH;
    }
}function onControl(number, value)
{
	
}
 