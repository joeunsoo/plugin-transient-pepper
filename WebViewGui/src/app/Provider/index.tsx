import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import SnackbarProvider from './SnackbarProvider';
import ControlParameterProvider from './ControlParameterProvider';
import ActivateProvider from './ActivateProvider';
import IsDebug from './IsDebug';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      {children}
      <IsDebug />
      <ActivateProvider />
      <AboutProvider />
      <AnalysisDataProvider />
      <SnackbarProvider />
      <ControlParameterProvider />
    </MuiProvider>
  );
}
