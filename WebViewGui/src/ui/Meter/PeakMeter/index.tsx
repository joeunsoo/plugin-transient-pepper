import Stack, { type StackProps } from '@mui/material/Stack';
import Led from './Led';

interface PageProps extends StackProps {
  idx: number,
  length?: number
}

export default function Page({
  idx,
  length = 7,
  sx,
  ...props
}: PageProps) {
  const thresholds = Array.from(
    { length },
    (v, i) => (1 - ((1 / length) * (i + 1)))
  );

  return (
    <Stack
      spacing={1.5}
      sx={{
        height:'100%',
        flexGrow: 1,
        ...sx
      }}
      {...props}
    >
      {thresholds.map((value, index) => (
        <Led
          key={index}
          idx={idx}
          startLevel={value}
          endLevel={thresholds[index - 1] || 1}
          mix={index / length}
        />
      ))}
    </Stack>
  );
}
