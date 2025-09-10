import Stack from '@mui/material/Stack';
import Led from './Led';

type PageProps = {
  id: number
  length?: number,
}

export default function Page({
  id,
  length = 7,
}: PageProps) {
  const thresholds = Array.from(
    { length },
    (v, i) => (1 - ((1 / length) * (i + 1)))
  );

  return (
    <Stack
      spacing={1}
      sx={{
        flexGrow: 1,
        height: '100%'
      }}
    >
      {thresholds.map((value, index) => (
        <Led
          key={index}
          id={id}
          startLevel={value}
          endLevel={thresholds[index-1] || 1}
          mix={index / length}
        />
      ))}
    </Stack>
  );
}
