
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';
import FreqBandInfo from '@/ui/FreqBandInfo';
import StyledMainPaper from '../ui/StyledMainPaper';

export default function App() {
  return (
    <Provider>
      <Box
        sx={{
          display: 'flex',
          minHeight: '100dvh',
          overflow: 'hidden',
        }}
      >
        <FreqBandInfo />
        <Stack
          sx={{
            flexGrow: 1,
            px: 5,
            pt: 1,
            pb: 5,
          }}
        >
          <Header />
          <Stack
            alignItems="center"
            justifyContent="center"
            sx={{
              height: '100%',
            }}
          >
            <StyledMainPaper
              sx={{
                width: '100%',
                height: '100%',
                display: 'flex',
                borderRadius: 5,
              }}
            >
              <Main />
            </StyledMainPaper>
          </Stack>
        </Stack>
      </Box>
    </Provider>
  );
}
