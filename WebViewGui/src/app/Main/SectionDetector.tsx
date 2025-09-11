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
        spacing="var(--column-spacing)"
        sx={{
          flexWrap: 'wrap',
          position: 'relative'
        }}
      >
        <Stack
          spacing="var(--row-spacing)"
        >
          <JuceKnob
            identifier="thresholdSlider"
            defaultValue={0.5}
            subDigit={1}
            ringColor="secondary"
          />
          <JuceToggleButton
            identifier="linkChannelsToggle"
            title="L/R Link"
          />
        </Stack>
        <JuceKnob
          identifier="emphasisSlider"
          defaultValue={0.5}
          subDigit={1}
        />
        <Stack
          spacing="var(--row-spacing)"
        >
          <JuceKnob
            identifier="bpfFrequencySlider"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceToggleButton
            identifier="bpfPowerToggle"
            title="BPF On"
          />
        </Stack>
      </Stack>
    </Stack>
  );
}
