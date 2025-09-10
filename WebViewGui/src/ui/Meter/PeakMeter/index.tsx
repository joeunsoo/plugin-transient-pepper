import Stack, { type StackProps } from '@mui/material/Stack';
import Led from './Led';
import Container from '@mui/material/Container';

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
    <Container>
      <Stack
        spacing={1.5}
        sx={{
          flexGrow: 1,
          backgroundColor:'#ff0000',
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
    </Container>
  );
}
