import React, { Component } from 'react';
import './App.css';

class App extends Component {
  constructor(props) {
    super(props);
    this.state = { 
      firstName : ''
      , lastName : ''
      , email : ''  
    };
  }

  inputChanged = (event) => {
    this.setState({ [event.target.name] : event.target.value });
  }

  handleSubmit = (event) => {
    alert(`Hello ${this.state.firstName} ${this.state.lastName}`);
    event.preventDefault();
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <label>First name </label>
        <input type="text" name="firstName" onChange={this.inputChanged} value={this.state.firstName} /><br />
        <label>Last name </label>
        <input type="text" name="lastName" onChange={this.inputChanged} value={this.state.lastName} /><br />
        <label>Email </label>
        <input type="text" name="email" onChange={this.inputChanged} value={this.state.email} /><br />
        <input type="submit" value="Press me" />
      </form>
    );
  }

}

export default App;
