import Stack from '@mui/material/Stack';

import SectionDetector from './SectionDetector';
import SectionShape from './SectionShape';
import SectionMix from './SectionMix';
import SectionTone from './SectionTone';
import SectionGraph from './SectionGraph';

export default function App() {

  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="space-between"
      spacing={5}
      sx={{
        p: 4,
        pb: 8,
        width: '100%',
        height: '100%',
        '> *': {
          height: '100%',
        },
        '--knob-width': '5.3em',
        '--row-spacing': '0.6em',
        '--column-spacing': '0.4em',
      }}
    >
      <Stack
        direction="column"
        justifyContent="space-between"
        spacing={5}
        sx={{
          flexShrink: 0,
        }}
      >
        <SectionDetector />
        <SectionShape />
      </Stack>
      <Stack
        direction="column"
        alignItems="end"
        justifyContent="end"
        spacing={5}
        sx={{
          flexGrow: 1,
        }}
      >
        <SectionGraph />
        <SectionTone />
      </Stack>
      <Stack
        direction="row"
        sx={{
          flexShrink: 0,
        }}
      >
        <SectionMix />
      </Stack>
    </Stack>
  );
}
