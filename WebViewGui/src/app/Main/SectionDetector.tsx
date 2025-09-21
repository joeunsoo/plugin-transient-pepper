import { useState } from 'react';

import { Box, Group, Stack, type StackProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { useControlStore } from '@/store/ControlStore';
import { HeadphonesIcon } from '@phosphor-icons/react';

export default function Page({
  sx, ...props
}: StackProps) {
  const [bpfOn, setBpfOn] = useState<boolean>(true);
  const { sidechainListen, setThreshold, setSidechainListen } = useControlStore();

  return (
    <Stack
      justify="space-between"
      gap="var(--row-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Transient Detector
      </SectionTitle>
      <Group
        justify="start"
        gap="var(--column-spacing)"
      >
        <JuceToggleButton
          identifier="linkChannelsToggle"
          title="L/R Link"
        />
        <JuceToggleButton
          identifier="bpfPowerToggle"
          title="BPF"
          onChange={(e, value) => setBpfOn(!value)}
          w="2.5em"
          px={0}
        />
        <JuceToggleButton
          identifier="sidechainListenToggle"
          title={
            <Box lh={0}>
              <HeadphonesIcon size="var(--icon-size-xs)" />
            </Box>
          }
          onChange={(e, value) => setSidechainListen(!value)}
          w="2.5em"
          px={0}
        />
      </Group>

      <Group
        justify="start"
        gap="var(--column-spacing)"
      >
        <JuceKnob
          identifier="thresholdSlider"
          defaultValue={0.5}
          subDigit={1}
          ringColor="secondary"
          onChange={(v) => setThreshold(v)}
        />
        <JuceKnob
          identifier="bpfFrequencySlider"
          defaultValue={0.5}
          subDigit={1}
          addTest={[bpfOn && sidechainListen]}
        />
      </Group>
    </Stack>
  );
}
