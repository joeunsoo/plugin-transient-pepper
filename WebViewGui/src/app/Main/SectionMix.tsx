
import { useState } from 'react';

import { Box, Group, Stack, type GroupProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import NoiseGain from './NoiseGain';
import OutputGain from './OutputGain';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { uesControlStore } from '@/store/ControlStore';

type PageProps = Omit<GroupProps, 'gap'>

export default function Page({
  ...props
}: PageProps) {
  const [wetSolo, setWetSolo] = useState<boolean>(false);
  const { sidechainListen } = uesControlStore();

  return (
    <Group
      align="center"
      justify="end"
      gap="var(--column-spacing)"
      sx={{
        '> *': {
          height: '100%',
        },
      }}
      {...props}
    >
      <Stack
        align="center"
        justify="end"
        gap="var(--row-spacing)"
      >
        <Box
          sx={{ flexGrow: 1 }}
        >
          <NoiseGain h="100%" />
        </Box>
        <JuceToggleButton
          identifier="wetSoloToggle"
          title="Wet Solo"
          onChange={(e, value) => setWetSolo(value)}
          addTest={[!sidechainListen]}
        />
        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
          addTest={[wetSolo, !sidechainListen]}
        />
      </Stack>

      <OutputGain />
    </Group>
  );
}
