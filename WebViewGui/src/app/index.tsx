
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';

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
        <Stack sx={{ flexGrow: 1 }}>
          <Header />
          <Main />
        </Stack>
      </Box>
    </Provider>
  );
}
