import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import Box from '@mui/material/Box';
import SectionTitle from './SectionTitle';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="end"
      justifyContent="space-between"
      spacing="var(--column-spacing)"
      sx={{
        pt:'2.8em',
        ...sx
      }}
      {...props}
    >
      <Stack
        direction="row"
        spacing="var(--column-spacing)"
        sx={{ position: 'relative' }}
      >
        <Box
          sx={{
            position: 'absolute',
            left: 0,
            top: '-1.8em'
          }}
        >
          <SectionTitle>
            Transient Detector
          </SectionTitle>
        </Box>
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

        <Stack
          sx={{ position: 'relative' }}
        >
          <Box
            sx={{
              position: 'absolute',
              left: 0,
              top: '-2.5em'
            }}
          >
            <JuceToggleButton
              identifier="bpfPowerToggle"
              title="BPF On"
            />
          </Box>
          <JuceKnob
            identifier="bpfFrequencySlider"
            defaultValue={0.5}
            subDigit={1}
          />
        </Stack>
      </Stack>
    </Stack>
  );
}
