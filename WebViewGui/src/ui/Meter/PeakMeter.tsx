'use client';

import Stack from '@mui/material/Stack';

import {
  motion,
  useMotionValue,
} from 'framer-motion';

export default function StyledMainPaper() {
  const x = useMotionValue(0);

  return (
    <Stack
      direction="row"
      sx={{
        width: '100%',
        height: '200px',
        backgroundColor: '#ffff00',
        '& > div': {
          backgroundColor: '#ff0000'
        }
      }}
    >
      <motion.div
        style={{
          width: '50%',
          height: x
        }}
      />
    </Stack>
  );
}
