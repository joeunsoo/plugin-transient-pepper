'use client';

import * as Juce from 'juce-framework-frontend';

import Button from '@mui/material/Button';

import { useSnackbarStore } from '@/src/store/SnackbarStore';

const sayHello = Juce.getNativeFunction('sayHello');

export default function App() {
  const { setOpen } = useSnackbarStore();

  return (
    <Button
      variant="contained"
      sx={{ marginTop: 2 }}
      onClick={() => {
        // eslint-disable-next-line @typescript-eslint/ban-ts-comment
        // @ts-ignore
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        sayHello('JUCE').then((result: any) => {
          setOpen(result);

          return null;
        }).catch(null);
      }}
    >
      Call
    </Button>
  );
}
