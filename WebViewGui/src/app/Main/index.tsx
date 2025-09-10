import Stack from '@mui/material/Stack';

import SectionDetect from './SectionDetect';
import SectionShape from './SectionShape';
import SectionLevel from './SectionLevel';

export default function App() {
  return (
    <Stack
      alignItems="center"
      justifyContent="center"
      sx={{
        px: 5,
        py: 5,
        flexGrow: 1,
        '& .MuiGrid-root': {
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          justifyContent: 'center',
        }
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="center"
        spacing={4}
        sx={{
          width: '100%',
          height: '100%',
          '> *': {
            height: '100%',
          }
        }}
      >
        <Stack
          alignItems="stretch"
          justifyContent="end"
          spacing={2}
          sx={{
            backgroundColor: 'var(--mui-palette-secondary-darkermost)',
            border: '1px solid var(--mui-palette-secondary-darken)',
            boxShadow: `
              0 1px 2px rgba(0,0,0,0.2),
              inset 0 1px 0 rgba(255,255,255,0.5);
            `,
            borderRadius: 3,
            '> *': {
              flexGrow: 1
            },
            '--knob-width': '6.0em'
          }}
        >
          <SectionDetect />
          <SectionShape />
        </Stack>
        <SectionLevel
          sx={{ flexShrink: 0 }}
        />
      </Stack>
    </Stack>
  );
}
