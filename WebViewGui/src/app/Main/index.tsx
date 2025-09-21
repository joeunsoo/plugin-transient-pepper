import { Group, rem, Stack } from '@mantine/core';
import { mantineSpace } from '@/define';
import SectionDetector from './SectionDetector';
import SectionGraph from './SectionGraph';
import SectionMix from './SectionMix';
import SectionShape from './SectionShape';
import SectionTone from './SectionTone';

export default function App() {
  return (
    <Group
      p={rem(mantineSpace * 4)}
      pb={rem(mantineSpace * 6)}
      align="center"
      justify="space-between"
      gap={rem(mantineSpace * 5)}
      w="100%"
      h="100%"
      style={{
        '--knob-width': '5.3em',
        '--row-spacing': '0.6em',
        '--column-spacing': '0.4em',
      }}
      sx={{
        '> *': {
          height: '100%',
        },
      }}
    >
      <Stack justify="space-between">
        <SectionDetector />
        <SectionShape />
      </Stack>

      <Stack gap={rem(mantineSpace * 5)} sx={{ flexGrow: 1 }}>
        <SectionGraph />
        <SectionTone sx={{ width: '100%' }} />
      </Stack>

      <Group align="stretch">
        <SectionMix />
      </Group>
    </Group>
  );
}
