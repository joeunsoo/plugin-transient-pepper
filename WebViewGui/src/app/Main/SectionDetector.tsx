import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="column"
      justifyContent="space-between"
      spacing="var(--column-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Transient Detector
      </SectionTitle>
      <Stack
        direction="row"
        justifyContent="space-between"
        spacing="var(--column-spacing)"
      >
        <JuceToggleButton
          identifier="linkChannelsToggle"
          title="L/R Link"
        />
        <JuceToggleButton
          identifier="bpfPowerToggle"
          title="BPF On"
        />
      </Stack>

      <Stack
        direction="row"
        justifyContent="space-between"
        spacing="var(--column-spacing)"
      >
        <JuceKnob
          identifier="thresholdSlider"
          defaultValue={0.5}
          subDigit={1}
          ringColor="secondary"
        />
        <JuceKnob
          identifier="emphasisSlider"
          defaultValue={0.5}
          subDigit={1}
        />
        <JuceKnob
          identifier="bpfFrequencySlider"
          defaultValue={0.5}
          subDigit={1}
        />
      </Stack>
    </Stack>
  );
}
