open ReasonUIKit;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(State.reducer, State.initialState);

  React.useEffect0(() => {
    let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timer));
  });

  <div className="uk-flex uk-flex-center uk-flex-middle uk-height-viewport">
    <div className="uk-position-top">
      <div className="uk-container uk-container-small">
        <h3 className="uk-text-center"> {React.string("Pomodoro")} </h3>
      </div>
    </div>
    <div className="uk-card uk-card-default uk-card-body">
      <h3 className="uk-card-title uk-text-center">
        {switch (state.currentPhase) {
         | Work => React.string("Focus")
         | Play => React.string("Break")
         }}
      </h3>
      <Timer seconds={state.seconds} />
      <div className="button-group">
        {if (state.isTicking) {
           <Button style=Button.StyleDanger onClick={_ => dispatch(Stop)}>
             <Icon icon=Icon.Ban />
           </Button>;
         } else {
           <Button style=Button.StylePrimary onClick={_ => dispatch(Start)}>
             <Icon icon=Icon.PlayCircle />
           </Button>;
         }}
        {let disabled =
           switch (state.currentPhase, state.seconds) {
           | (Play, seconds) => seconds == state.playTime
           | (Work, seconds) => seconds == state.workTime
           };

         <Button
           style=Button.StyleSecondary
           onClick={_ => dispatch(Reset)}
           disabled>
           <Icon icon=Icon.Refresh />
         </Button>}
      </div>
      <div className="uk-margin-top">
        <EditPhaseTime
          phase="Work"
          value={state.workTime}
          onChange={e => dispatch(SetTime(Work, e))}
        />
        <EditPhaseTime
          phase="Play"
          value={state.playTime}
          onChange={e => dispatch(SetTime(Play, e))}
        />
      </div>
    </div>
  </div>;
};
