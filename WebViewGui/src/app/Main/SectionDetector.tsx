import { useState } from 'react';
import { HeadphonesIcon } from '@phosphor-icons/react';
import { Box, Group, Stack, type StackProps } from '@mantine/core';
import { useControlStore } from '@/store/ControlStore';
import { usePluginStore } from '@/store/PluginStore';
import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import SectionTitle from './SectionTitle';

export default function Page({ sx, ...props }: StackProps) {
  const [bpfOn, setBpfOn] = useState<boolean>(true);
  const { sidechainListen, setThreshold, setSidechainListen } = useControlStore();
  const { numChannels } = usePluginStore();

  return (
    <Stack
      justify="space-between"
      gap="var(--row-spacing)"
      sx={{
        ...sx,
      }}
      {...props}
    >
      <SectionTitle>Transient Detector</SectionTitle>
      <Group justify="start" gap="var(--column-spacing)">
        <JuceToggleButton
          identifier="linkChannelsToggle"
          title={numChannels < 2 ? 'Mono' : 'L/R Link'}
          addTest={[numChannels < 2]}
        />
        <JuceToggleButton
          identifier="bpfPowerToggle"
          title="BPF"
          onChange={(_e, value) => setBpfOn(!value)}
          w="2.5em"
          px={0}
        />
        <JuceToggleButton
          identifier="sidechainListenToggle"
          title={
            <Box lh={0}>
              <HeadphonesIcon size="0.9rem" />
            </Box>
          }
          onChange={(_e, value) => setSidechainListen(!value)}
          w="2.5em"
          px={0}
        />
      </Group>

      <Group justify="start" gap="var(--column-spacing)">
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
