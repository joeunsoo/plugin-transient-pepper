'use client';

import { useSnackbarStore } from '@/store/SnackbarStore';
import * as Juce from 'juce-framework-frontend';

import dayjs from 'dayjs';

import Button from '@mui/material/Button';

import { useActivateStore } from '@/store/ActivateStore';
import { useEffect, useState } from 'react';

const startTrial = Juce.getNativeFunction('startTrial');
const getTrial = Juce.getNativeFunction('getTrial');

export default function LoginForm() {
  const { setTrial, setOpen } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [isTrial, setIsTrial] = useState<boolean>(false);
  const [trialDays, setTrialDays] = useState<number>(0);
  const [isEnded, setIsEnded] = useState<boolean>(false);

  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    getTrial().then((result: number) => {
      if (result > 0) {
        setIsTrial(true);
      } else {
        setIsTrial(false);
      }
      const now = dayjs();
      const end = dayjs(result).add(30, 'day');
      if (result > 0 && now.isAfter(end)) {
        setIsEnded(true);

        return null;
      } else {
        setIsEnded(false);
      }
      const diffMs = end.diff(now);              // end - now (밀리초)
      const diffDays = Math.ceil(diffMs / (1000 * 60 * 60 * 24));

      setTrialDays(diffDays);

      return null;
    }).catch(console.error);
  }, []);

  let message = 'Start Trial (30 days)';
  if (isEnded) {
    message = 'Trial Ended';
  } else if (isTrial) {
    message = `Continue Trial (${trialDays} days remaining)`;
  }

  return (
    <Button
      disabled={isEnded}
      onClick={() => {
        // eslint-disable-next-line @typescript-eslint/ban-ts-comment
        // @ts-ignore
        startTrial().then((result: number) => {
          setTrial(result);
          setOpen(false);
          enqueueSnackbar('Trial Start', { variant: 'success' });

          return null;
        }).catch(console.error);
      }}
      variant="outlined"
      sx={{
        width: '100%',
        color: !isEnded ? 'var(--mui-palette-primary-lighter)' : 'var(--mui-palette-primary-light)'
      }}
    >
      {message}
    </Button>
  );
}
