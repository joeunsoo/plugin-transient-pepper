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
        px:5,
        py:5,
        flexGrow: 1,
        '--Grid-borderWidth': '1px',
        '& > div': {
          borderRight: 'var(--Grid-borderWidth) solid',
          borderColor: 'divider',
        },
        '& > div:last-child': {
          borderRight: 'none',
        },
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
        sx={{
          display: 'grid',
          gridTemplateColumns: '2fr 2fr 3fr',
          width: '100%',
          height: '100%',
          '> *': {
            height: '100%',
          }
        }}
      >
        <SectionDetect />
        <SectionShape />
        <SectionLevel />
      </Stack>
    </Stack>
  );
}
