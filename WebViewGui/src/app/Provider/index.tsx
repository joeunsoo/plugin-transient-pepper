import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import SnackbarProvider from './SnackbarProvider';
import ControlParameterProvider from './ControlParameterProvider';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      {children}
      <AboutProvider />
      <AnalysisDataProvider />
      <SnackbarProvider />
      <ControlParameterProvider />
    </MuiProvider>
  );
}
