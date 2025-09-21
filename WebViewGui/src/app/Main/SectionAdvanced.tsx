import { Stack } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

export default function App() {
  return (
    <Stack
      align="center"
      justify="center"
      sx={{
        display: 'grid',
        gridTemplateColumns: 'repeat(2, 1fr)',
      }}
    >
      <JuceKnob
        identifier="fastAttackSlider"
        defaultValue={0.5}
        subDigit={4}
      />
      <JuceKnob
        identifier="fastReleaseSlider"
        defaultValue={0.5}
        subDigit={4}
      />
      <JuceKnob
        identifier="slowAttackSlider"
        defaultValue={0.5}
        subDigit={4}
      />
      <JuceKnob
        identifier="slowReleaseSlider"
        defaultValue={0.5}
        subDigit={4}
      />
    </Stack>
  );
}
