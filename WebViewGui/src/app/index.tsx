import { Box, rem, Stack } from '@mantine/core';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';
import { GlassSx, mantineSpace } from '@/define';

export default function App() {
  return (
    <Provider>
      <Box
        style={{
          display: 'flex',
          minHeight: '100dvh',
          overflow: 'hidden',
          userSelect: 'none',
        }}
      >
        <Stack
          px={rem(mantineSpace * 3)}
          pb={rem(mantineSpace * 2)}
          sx={{
            flexGrow: 1,
          }}
        >
          <Header />
          <Stack
            align="center"
            justify="center"
            sx={{
              height: '100%',
            }}
          >
            <Box
              w="100%"
              h="100%"
              sx={{
                display: 'flex',
                borderRadius: rem(mantineSpace * 5),
                background: `
                  linear-gradient(
                    to bottom,
                    rgba(255,255,255,0.1),
                    rgba(255,255,255,0) 100%
                  )
                `,
                ...GlassSx
              }}
            >
              <Main />
            </Box>
          </Stack>
        </Stack>
      </Box>
    </Provider>
  );
}
